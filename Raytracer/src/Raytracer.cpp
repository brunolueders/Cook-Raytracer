#include "Raytracer.hpp"

namespace cook {
    
    bool RaytracerSettings::valid() const {
        return (canvas != nullptr && scene != nullptr && numSubpixels > 0 &&
                numSamplesPerSubpixel > 0 && maxRecursionDepth > 0 &&
                maxThreads > 0);
    }

    size_t Raytracer::getPrototype(float a_u, float a_v) {
        auto i = static_cast<size_t>(std::floor(3.f*a_u))%3;
        auto j = static_cast<size_t>(std::floor(3.f*a_v))%3;
        return m_settings.prototypePattern[j*3 + i];
    }

    Ray Raytracer::pixelRay(float a_u, float a_v) {
        // Calculate focal point from pixel coordinates
        auto dir = m_settings.canvas->pixelToCamera(a_u, a_v, m_settings.scene->camera().near()).normalize();
        auto focalPoint = m_settings.scene->camera().calculateFocalPoint(dir);

        // Sample aperture disc
        auto prototype = getPrototype(a_u, a_v);
        auto apertureSample = m_settings.scene->camera().sampleAperture(prototype);

        // Create primary ray
        dir = (focalPoint - apertureSample).normalize();
        auto length = m_settings.scene->camera().distanceToFarPlane(dir);
        return Ray{ apertureSample, dir, length, prototype };
    }

    Colour Raytracer::trace(Ray& a_ray, unsigned a_depth) {
        if(a_depth >= m_settings.maxRecursionDepth) {
            return Colour{};
        }

        auto colour = m_settings.scene->backgroundColour();
        IntersectionInfo info;
        if(m_settings.scene->closestIntersection(a_ray, &info)) {
            const auto mat = info.material;
            auto eps = 1e-3f;

            // Shadow rays
            colour = m_settings.scene->ambientLight()*mat->ambient();
            for(auto lightIt = m_settings.scene->lightsBegin(); lightIt != m_settings.scene->lightsEnd(); ++lightIt) {
                // Construct shadow ray to random point on light source
                auto samplePoint = lightIt->sample(info.point, info.normal, a_ray.prototype());
                Ray shadowRay{ info.point + info.normal*eps, samplePoint, a_ray.prototype() };
                if(!m_settings.scene->doesIntersect(shadowRay)) {
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

    void Raytracer::renderPixelRange(const size_t x0, const size_t y0, const size_t x1, const size_t y1) {
        const auto subpixelsSq = static_cast<float>(m_settings.numSubpixels*m_settings.numSubpixels);
        const auto subpixelSpacing = 1.f/m_settings.numSubpixels;

        for(size_t y = y0; y <= y1; ++y) {
            for(size_t x = x0; x <= x1; ++x) {
                Colour colour;
                for(size_t sy = 0; sy < m_settings.numSubpixels; ++sy) {
                    for(size_t sx = 0; sx < m_settings.numSubpixels; ++sx) {
                        for(size_t k = 0; k < m_settings.numSamplesPerSubpixel; k++) {
                            auto offsX = (static_cast<float>(sx) + urand())*subpixelSpacing;
                            auto offsY = (static_cast<float>(sy) + urand())*subpixelSpacing;
                            auto ray = pixelRay(static_cast<float>(x) + offsX, static_cast<float>(y) + offsY);
                            colour += trace(ray)/static_cast<float>(m_settings.numSamplesPerSubpixel);
                        }
                    }
                }
                m_settings.canvas->setPixel(x, y, colour/subpixelsSq);
                ++m_pixelsRendered;
            }
        }
    }

    void Raytracer::render()
    {
        if(!m_settings.valid()) {
            throw std::exception("ERROR: Invalid raytracer settings.");
        }

        m_pixelsRendered = 0;

        const auto w = m_settings.canvas->width();
        const auto h = m_settings.canvas->height();
        std::thread t1(&Raytracer::renderPixelRange, this, 0, 0, w/2, h/2);
        std::thread t2(&Raytracer::renderPixelRange, this, w/2+1, 0, w-1, h/2);
        std::thread t3(&Raytracer::renderPixelRange, this, 0, h/2+1, w/2, h-1);
        std::thread t4(&Raytracer::renderPixelRange, this, w/2+1, h/2+1, w-1, h-1);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }

    float Raytracer::progress() const {
        return static_cast<float>(m_pixelsRendered)/static_cast<float>(m_settings.canvas->size());
    }

    RaytracerSettings & Raytracer::settings() {
        return m_settings;
    }

}
