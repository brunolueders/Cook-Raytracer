#pragma once
#include "Canvas.hpp"
#include "Scene.hpp"
#include <thread>
#include <atomic>

namespace cook {

    struct RaytracerSettings {
        unsigned numSubpixels{ 2 };
        unsigned numSamplesPerSubpixel{ 2 };
        unsigned maxRecursionDepth{ 3 };
        unsigned maxThreads{ std::thread::hardware_concurrency() };

        std::array<size_t, 9> prototypePattern{ 1, 0, 6, 2, 7, 8, 4, 3, 5 };

        Canvas* canvas{ nullptr };
        Scene*  scene{ nullptr };

        bool valid() const;
    };

    class Raytracer {
    protected:
        RaytracerSettings   m_settings;
        std::atomic<size_t> m_pixelsRendered;

    public:
        size_t getPrototype(float a_u, float a_v);
        Ray    pixelRay(float a_u, float a_v);
        Colour trace(Ray& a_ray, unsigned a_depth = 0);

        void renderPixelRange(const size_t x0, const size_t y0, const size_t x1, const size_t y1);
        void render();

        float progress() const;

        RaytracerSettings& settings();
    };

}
