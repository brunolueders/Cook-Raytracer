#include "View.hpp"
#include "Scene.hpp"
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>

namespace cook {

    class Raytracer final {
    protected:
        std::unique_ptr<View> m_view;

        Scene m_scene;

        struct {
            const std::string outputFilename = "box18.png";

            const size_t vpWidth{ 400 };
            const size_t vpHeight{ 300 };

            const Vec3  camDefaultUp{ -Vec3::unitY };
            const Vec3  camPos{ .0f, 25.f, 55.f };
            const Vec3  camTarget{ 0.f, 25.0f, 0.f };

            const float camFOV{ PI180*60.f };
            const float camFarPlane{ 400.f };
            const float camFocalLength{ 55.f };
            const float camAperture{ 1.f };

            const unsigned numSubpixels{ 2 };
            const unsigned numSamplesPerSubpixel{ 2 };
            const unsigned maxRecursionDepth{ 3 };
            
            const Colour backgroundColour{};
            const Colour ambientLightColour{ .2f, .2f, .2f };

        } const m_settings;

    public:
        Raytracer() {}

        void init() {
            m_view = std::make_unique<View>(m_settings.vpWidth, m_settings.vpHeight, m_settings.camPos, m_settings.camTarget, m_settings.camDefaultUp,
                                            m_settings.camFOV, m_settings.camFarPlane, m_settings.camFocalLength, m_settings.camAperture);

            try {
                m_scene.loadFromStream(std::ifstream("assets/simple.scene.json"), false);
            }
            catch(std::exception& ex) {
                std::cerr << ex.what() << std::endl;
                terminate();
            }
        }

        Colour trace(Ray& a_ray, unsigned a_depth = 0) {
            if(a_depth >= m_settings.maxRecursionDepth) {
                return Colour{};
            }

            auto colour = m_settings.backgroundColour;
            IntersectionInfo info;
            if(m_scene.closestIntersection(a_ray, &info)) {
                const auto mat = info.material;
                auto eps = 1e-3f;

                // Shadow rays
                colour = m_settings.ambientLightColour*mat->ambient();
                for(auto lightIt = m_scene.lightsBegin(); lightIt != m_scene.lightsEnd(); ++lightIt) {
                    // Construct shadow ray to random point on light source
                    auto samplePoint = lightIt->sample(info.point, info.normal, a_ray.prototype());
                    Ray shadowRay{ info.point + info.normal*eps, samplePoint, a_ray.prototype() };
                    if(!m_scene.doesIntersect(shadowRay)) {
                        // Phong shading
                        auto intensity = shadowRay.direction().dot(info.normal);
                        if(intensity > 0.f) {
                            colour += intensity*lightIt->colour()*mat->diffuse();
                        }
                    }
                }

                // Reflection
                if(mat->isReflective()) {
                    auto reflDir = mat->sampleReflectionFunction(a_ray, info.normal);
                    Ray reflRay{ info.point + reflDir*eps, reflDir, a_ray.length(), a_ray.prototype() };
                    colour += trace(reflRay, a_depth + 1)*mat->specular();
                }

                // Refraction
                if(mat->isTransparent()) {
                    auto refrDir = mat->sampleRefractionFunction(a_ray, info.normal);
                    if(refrDir != Vec3::zero) {
                        Ray refrRay{ info.point + refrDir*eps, refrDir, a_ray.length(), a_ray.prototype() };
                        colour += trace(refrRay, a_depth + 1)*mat->transmissive();
                    }
                }
            }

            return colour;
        }

        std::atomic<size_t> progress{ 0 };

        void renderPixelRange(const size_t x0, const size_t y0, const size_t x1, const size_t y1) {
            static const auto subpixelsSq = static_cast<float>(m_settings.numSubpixels*m_settings.numSubpixels);
            static const auto subpixelSpacing = 1.f/m_settings.numSubpixels;

            const auto numPixels = m_settings.vpHeight*m_settings.vpWidth/100;
            for(size_t y = y0; y <= y1; ++y) {
                for(size_t x = x0; x <= x1; ++x) {
                    Colour colour;
                    for(size_t sy = 0; sy < m_settings.numSubpixels; ++sy) {
                        for(size_t sx = 0; sx < m_settings.numSubpixels; ++sx) {
                            for(size_t k = 0; k < m_settings.numSamplesPerSubpixel; k++) {
                                auto offsX = (static_cast<float>(sx) + urand())*subpixelSpacing;
                                auto offsY = (static_cast<float>(sy) + urand())*subpixelSpacing;
                                auto ray = m_view->pixelRay(static_cast<float>(x) + offsX, static_cast<float>(y) + offsY);
                                colour += trace(ray)/static_cast<float>(m_settings.numSamplesPerSubpixel);
                            }
                        }
                    }
                    m_view->setPixel(x, y, colour/subpixelsSq);
                    if(++progress%numPixels == 0) {
                        std::cout << progress/numPixels << "%\r";
                    }
                }
            }
        }

        void render() {
            const auto w = m_settings.vpWidth;
            const auto h = m_settings.vpHeight;
            std::thread t1(&Raytracer::renderPixelRange, this, 0, 0, w/2, h/2);
            std::thread t2(&Raytracer::renderPixelRange, this, w/2+1, 0, w-1, h/2);
            std::thread t3(&Raytracer::renderPixelRange, this, 0, h/2+1, w/2, h-1);
            std::thread t4(&Raytracer::renderPixelRange, this, w/2+1, h/2+1, w-1, h-1);
            t1.join();
            t2.join();
            t3.join();
            t4.join();
            m_view->writeToPNG(m_settings.outputFilename);
        }
    };

}

int main(void) {
    cook::Raytracer renderer;
    renderer.init();
    renderer.render();
    return 0;
}
