#include "View.hpp"
#include "Object.hpp"
#include "Sphere.hpp"
#include "Rectangle.hpp"
#include "ResourceMap.hpp"
#include "Ray.hpp"
#include "Light.hpp"
#include "Mat44.hpp"
#include "Util.hpp"
#include <iostream>
#include <thread>
#include <atomic>

namespace cook {

    class Raytracer final {
    protected:
        std::unique_ptr<View> m_view;

        std::vector<std::unique_ptr<Material>>   m_materials;
        std::vector<std::unique_ptr<Shape>>      m_shapes;
        std::vector<std::unique_ptr<Object>>     m_objects;
        std::vector<std::unique_ptr<Light>>      m_lights;

        struct {
            const std::string outputFilename = "box13.png";

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

            m_materials.emplace_back(new Material{ Colour{.9f, .9f, .9f}, Colour{.9f, .9f, .9f}, Colour{}, Colour{}, 1.f, 1.f, 1.f });
            m_materials.emplace_back(new Material{ Colour{1.f, .4f, .4f}, Colour{1.f, .4f, .4f}, Colour{}, Colour{}, 1.f, 1.f, 1.f });
            m_materials.emplace_back(new Material{ Colour{.4f, .4f, 1.f}, Colour{.4f, .4f, 1.f}, Colour{}, Colour{}, 1.f, 1.f, 1.f });

            m_materials.emplace_back(new Material{ Colour{}, Colour{}, Colour{ .2f, .2f, .2f }, Colour{ 1.f, 1.f, 1.f }, 10.f, 10.f, 1.05f });
            m_materials.emplace_back(new Material{ Colour{ .4f, .2f, .6f }, Colour{.4f, .2f, .6f}, Colour{.4f, .2f, .6f}, Colour{}, 1000.f, 1.f, 1.f });
            m_materials.emplace_back(new Material{ Colour{ .3f, .6f, .8f }, Colour{.3f, .6f, .8f}, Colour{}, Colour{}, 1.f, 1.f, 1.f });

            m_shapes.emplace_back(new Rectangle{});
            m_objects.push_back(std::make_unique<Object>(m_shapes.back().get(), m_materials[0].get()));
            m_objects.back()->transform().setScale(Vec3{ 50.f, 50.f, 50.f });

            m_objects.push_back(std::make_unique<Object>(m_shapes.back().get(), m_materials[0].get()));
            m_objects.back()->transform().setPosition(Vec3{ 0.f, 50.f, 0.f });
            m_objects.back()->transform().setScale(Vec3{ 50.f, 50.f, 50.f });
            m_objects.back()->transform().setRotation(Vec3{ 180.f, 0.f, 0.f });

            m_objects.push_back(std::make_unique<Object>(m_shapes.back().get(), m_materials[0].get()));
            m_objects.back()->transform().setPosition(Vec3{ 0.f, 25.f, -25.f });
            m_objects.back()->transform().setScale(Vec3{ 50.f, 50.f, 50.f });
            m_objects.back()->transform().setRotation(Vec3{ 90.f, 0.f, 0.f });

            m_shapes.emplace_back(new Rectangle{});
            m_objects.push_back(std::make_unique<Object>(m_shapes.back().get(), m_materials[1].get()));
            m_objects.back()->transform().setPosition(Vec3{ 25.f, 25.f, 0.f });
            m_objects.back()->transform().setScale(Vec3{ 50.f, 50.f, 50.f });
            m_objects.back()->transform().setRotation(Vec3{ 0.f, 0.f, 90.f });

            m_shapes.emplace_back(new Rectangle{});
            m_objects.push_back(std::make_unique<Object>(m_shapes.back().get(), m_materials[2].get()));
            m_objects.back()->transform().setPosition(Vec3{ -25.f, 25.f, 0.f });
            m_objects.back()->transform().setScale(Vec3{ 50.f, 50.f, 50.f });
            m_objects.back()->transform().setRotation(Vec3{ 0.f, 0.f, -90.f });

            m_shapes.emplace_back(new Sphere{});
            m_objects.push_back(std::make_unique<Object>(m_shapes.back().get(), m_materials[3].get()));
            m_objects.back()->transform().setPosition(Vec3{ 10.f, 10.f, -5.f });
            m_objects.back()->transform().setScale(Vec3{ 10.f, 10.f, 10.f });

            m_shapes.emplace_back(new Sphere{});
            m_objects.push_back(std::make_unique<Object>(m_shapes.back().get(), m_materials[4].get()));
            m_objects.back()->transform().setPosition(Vec3{ -10.f, 30.f, 0.f });
            m_objects.back()->transform().setScale(Vec3{ 8.f, 8.f, 8.f });

            m_shapes.emplace_back(new Sphere{});
            m_objects.push_back(std::make_unique<Object>(m_shapes.back().get(), m_materials[5].get()));
            m_objects.back()->transform().setPosition(Vec3{ -5.f, 6.f, 5.f });
            m_objects.back()->transform().setScale(Vec3{ 6.f, 6.f, 6.f });

            m_lights.emplace_back(new Light{ Vec3{ 0.f, 40.f, 0.f }, 5.f, Colour{ 1.2f, 1.2f, 1.2f } });
        }

        bool closestIntersection(const Ray& a_ray, IntersectionInfo* a_info) {
            IntersectionInfo info, closestInfo;
            closestInfo.param = a_ray.length();
            closestInfo.index = m_objects.size();
            for(size_t i = 0; i < m_objects.size(); ++i) {
                if(m_objects[i]->intersect(a_ray, &info) && (info.param < closestInfo.param)) {
                    closestInfo = info;
                    closestInfo.index = i;
                }
            }

            if(closestInfo.index == m_objects.size()) {
                return false;
            }
            *a_info = closestInfo;
            return true;
        }

        bool obstructed(const Ray& a_ray) {
            IntersectionInfo info;
            for(const auto& obj: m_objects) {
                if(obj->intersect(a_ray, &info)) {
                    return true;
                }
            }
            return false;
        }

        Colour trace(const Ray& a_ray, unsigned a_depth = 0) {
            if(a_depth >= m_settings.maxRecursionDepth) {
                return Colour{};
            }

            auto colour = m_settings.backgroundColour;
            IntersectionInfo info;
            if(closestIntersection(a_ray, &info)) {
                const auto mat = m_objects[info.index]->material();
                auto eps = 1e-3f;

                // Shadow rays
                colour = m_settings.ambientLightColour*mat->ambient();
                for(const auto& light: m_lights) {
                    // Construct shadow ray to random point on light source
                    auto samplePoint = light->sample(info.point, info.normal, a_ray.prototype());
                    Ray shadowRay{ info.point + info.normal*eps, samplePoint, a_ray.prototype() };
                    if(!obstructed(shadowRay)) {
                        // Phong shading
                        auto intensity = shadowRay.direction().dot(info.normal);
                        if(intensity > 0.f) {
                            colour += intensity*light->colour()*mat->diffuse();
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
