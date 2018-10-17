#pragma once
#include "Canvas.hpp"
#include "Scene.hpp"
#include <atomic>

namespace cook {

    class Raytracer {
    protected:
        Canvas* m_canvas;
        Scene*  m_scene;

        unsigned m_numSubpixels;
        unsigned m_numSamplesPerSubpixel;
        unsigned m_maxRecursionDepth;

    public:
        Raytracer(Canvas* a_canvas, Scene* a_scene);

        Colour trace(Ray& a_ray, unsigned a_depth = 0);

        size_t getPrototype(float a_u, float a_v);

        Ray pixelRay(float a_u, float a_v);

        std::atomic<size_t> progress{ 0 };

        void renderPixelRange(const size_t x0, const size_t y0, const size_t x1, const size_t y1);

        void render(std::string a_filename, unsigned a_numSubpixels, unsigned a_samplesPerSubpixel,
                    unsigned a_maxRecursionDepth);
    };

}
