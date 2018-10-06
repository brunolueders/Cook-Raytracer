#include "View.hpp"
#include "Util.hpp"
#include "lodepng.h"
#include <cassert>
#include <array>

namespace cook {

    size_t _getPrototype(const float a_u, const float a_v) {
        static const std::array<size_t, 9> pattern{ 1, 0, 6, 2, 7, 8, 4, 3, 5 };
        auto i = static_cast<size_t>(std::floor(3.f*a_u))%3;
        auto j = static_cast<size_t>(std::floor(3.f*a_v))%3;
        return pattern[j*3 + i];
    }

    View::View(const std::size_t a_width, const std::size_t a_height, const Vec3& a_position,
               const Vec3& a_target, const Vec3& a_stdup, const float a_fov, const float a_far,
               const float a_focalLength, const float a_aperture) :
        m_width{a_width},
        m_height{a_height},
        m_size{a_width*a_height},
        m_aspect{static_cast<float>(a_width)/a_height},
        m_position{a_position},
        m_stdup{a_stdup},
        m_near{1.f/std::tan(a_fov/2.f)},
        m_far{a_far},
        m_focalLength{a_focalLength},
        m_aperture{a_aperture}
    {
        m_pixels.resize(m_size);
        lookAt(a_target);
    }

    std::size_t View::width() const {
        return m_width;
    }

    std::size_t View::height() const {
        return m_height;
    }

    std::size_t View::size() const {
        return m_size;
    }

    float View::aspect() const {
        return m_aspect;
    }

    Colour View::pixel(const std::size_t a_x, const std::size_t a_y) const {
        assert((a_x < m_width) && (a_y < m_height));
        return m_pixels[a_y*m_width + a_x];
    }

    void View::setPixel(const std::size_t a_x, const std::size_t a_y, const Colour& a_col) {
        assert((a_x < m_width) && (a_y < m_height));
        m_pixels[a_y*m_width + a_x] = a_col;
    }

    void View::writeToPNG(const std::string a_file) {
        // Convert rgb colour data (range: 0.0 - 1.0) to bytes (0 - 256)
        using ubyte = unsigned char;
        std::vector<ubyte> data(4*m_size);
        for(std::size_t i = 0; i < m_size; ++i) {
            m_pixels[i].clamp();
            m_pixels[i] *= 255.;
            data[4*i]   = static_cast<ubyte>(m_pixels[i].r);
            data[4*i+1] = static_cast<ubyte>(m_pixels[i].g);
            data[4*i+2] = static_cast<ubyte>(m_pixels[i].b);
            data[4*i+3] = 255;
        }

        // Output to file
        auto err = lodepng::encode(a_file, data, m_width, m_height);
        if(err) {
            throw ("LodePNG: Could not write to file " + a_file);
        }
    }

    void View::lookAt(const Vec3& a_target) {
        // Calculate the camera's local coordinate system from the
        // default up direction and the target position
        m_look = (a_target - m_position).normalize();
        m_up = (m_stdup - m_look.dot(m_stdup)*m_look).normalize();
        m_right = m_look.cross(m_up).normalize();
    }

    Ray View::pixelRay(const float a_u, const float a_v) const {
        // Calculate the focal point from the pixel coordinates
        Vec3 pixelCoords{
           (2.f*a_u/m_width - 1.f)*m_aspect, 
            2.f*a_v/m_height - 1.f,
            m_near };
        pixelCoords.normalize();
        auto focalPoint = (m_focalLength/pixelCoords.z)*pixelCoords;
        auto focalPointWorld = focalPoint.x*m_right + focalPoint.y*m_up + focalPoint.z*m_look + m_position;

        // Stratified jittered sampling of the aperture disc
        auto prototype = _getPrototype(a_u, a_v);
        auto incr = m_aperture*.5f/3.f;
        auto jitterMin = (prototype/3)*incr;
        auto r = lerp(urand(), jitterMin, jitterMin + incr);

        incr = TWOPI/3.f;
        jitterMin = (prototype%3)*incr;
        auto theta = lerp(urand(), jitterMin, jitterMin + incr);

        Vec3 apertureSample {
            r*std::cos(theta),
            r*std::sin(theta),
            0.f
        };

        auto apertureSampleWorld = apertureSample.x*m_right + apertureSample.y*m_up + m_position;
        
        // Create primary ray
        auto dir = (focalPointWorld - apertureSampleWorld).normalize();
        auto length = m_far/dir.dot(m_look);
        return Ray{ apertureSampleWorld, dir, length, prototype };
    }
}
