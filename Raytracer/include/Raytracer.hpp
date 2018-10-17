#pragma once
#include "Canvas.hpp"
#include "Scene.hpp"
#include <atomic>

namespace cook {

    class Raytracer {
    protected:
        Canvas m_canvas;
        Scene  m_scene;

        struct {
            const std::string outputFilename = "renders/box19.png";

            const size_t vpWidth{ 200 };
            const size_t vpHeight{ 150 };

            const unsigned numSubpixels{ 2 };
            const unsigned numSamplesPerSubpixel{ 2 };
            const unsigned maxRecursionDepth{ 3 };

        } const m_settings;

    public:
        Raytracer();

        void init();

        Colour trace(Ray& a_ray, unsigned a_depth = 0);

        size_t getPrototype(float a_u, float a_v);

        Ray pixelRay(float a_u, float a_v);

        std::atomic<size_t> progress{ 0 };

        void renderPixelRange(const size_t x0, const size_t y0, const size_t x1, const size_t y1);

        void render();
    };

}
