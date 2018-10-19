#include "Canvas.hpp"
#include "lodepng.h"
#include <cassert>

namespace cook {
    Canvas::Canvas() :
        Canvas{ 0, 0 }
    {}

    Canvas::Canvas(std::size_t a_width, std::size_t a_height) :
        m_width{ a_width },
        m_height{ a_height },
        m_size{ a_width*a_height },
        m_aspect{ static_cast<float>(a_width)/a_height },
        m_pixels( a_width*a_height )
    {}

    std::size_t Canvas::width() const {
        return m_width;
    }

    std::size_t Canvas::height() const {
        return m_height;
    }

    std::size_t Canvas::size() const {
        return m_size;
    }

    float Canvas::aspect() const {
        return m_aspect;
    }

    Colour Canvas::pixel(const std::size_t a_x, const std::size_t a_y) const {
        return m_pixels[a_y*m_width + a_x];
    }

    Vec3 Canvas::pixelToCamera(float a_u, float a_v, float a_near) const {
        // Convert pixel coordinates to a point on a camera's
        // near plane
        return Vec3{ (2.f*a_u/m_width - 1.f)*m_aspect,
                      2.f*a_v/m_height - 1.f,
                      a_near };
    }

    void Canvas::setPixel(const std::size_t a_x, const std::size_t a_y, const Colour & a_col) {
        m_pixels[a_y*m_width + a_x] = a_col;
    }

    void Canvas::writeToPNG(const std::string a_file) {
        // Convert rgb colour data (range: 0.0 - 1.0) to bytes (0 - 255)
        using ubyte = unsigned char;
        std::vector<ubyte> data(4*m_size);
        for(size_t i = 0; i < m_size; ++i) {
            m_pixels[i].clamp();
            m_pixels[i] *= 255.f;
            data[4*i] = static_cast<ubyte>(m_pixels[i].r);
            data[4*i+1] = static_cast<ubyte>(m_pixels[i].g);
            data[4*i+2] = static_cast<ubyte>(m_pixels[i].b);
            data[4*i+3] = 255;
        }

        // Output to file
        auto err = lodepng::encode(a_file, data, m_width, m_height);
        if(err) {
            throw std::exception(("LodePNG: Could not write to file " + a_file).c_str());
        }
    }

    void Canvas::loadFromPNG(const std::string a_file) {
        // Load from file
        std::vector<unsigned char> data;
        auto err = lodepng::decode(data, m_width, m_height, a_file);
        if(err) {
            throw std::exception(("LodePNG: Could not read from file " + a_file).c_str());
        }

        m_size = m_width*m_height;
        m_aspect = static_cast<float>(m_width)/m_height;
        m_pixels.resize(m_size);

        // Convert bytes (0 - 255) to float rgb (0.0 - 1.0)
        for(size_t i = 0; i < m_size; ++i) {
            m_pixels[i].r = static_cast<float>(data[4*i])/255.f;
            m_pixels[i].g = static_cast<float>(data[4*i+1])/255.f;
            m_pixels[i].b = static_cast<float>(data[4*i+2])/255.f;
        }
    }

}
