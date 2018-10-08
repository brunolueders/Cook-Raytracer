/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Virtual camera and canvas                           */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Ray.hpp"
#include "Colour.hpp"
#include <vector>

namespace cook {

    /* Combines scene camera and render target in a single class. */
    class View {
    protected:
        std::vector<Colour> m_pixels;
        std::size_t         m_width{ 0 };
        std::size_t         m_height{ 0 };
        std::size_t         m_size{ 0 }; // width*height
        float               m_aspect{ 0.f };
        float               m_focalLength{ 1.f };
        float               m_aperture{ 1.f };

        Vec3  m_position;
        Vec3  m_stdup; // The standard up direction
        Vec3  m_look, m_right, m_up; // The camera's local coordinate system
        float m_near{ 1.f }, m_far{ 2.f };

    public:
        View(const std::size_t a_width, const std::size_t a_height, const Vec3& a_position,
             const Vec3& a_target, const Vec3& a_stdup, const float a_fov, const float a_far,
             const float a_focalLength, const float a_aperture);

        std::size_t width() const;
        std::size_t height() const;
        std::size_t size() const;
        float       aspect() const;
        Colour      pixel(const std::size_t a_x, const std::size_t a_y) const;

        void setPixel(const std::size_t a_x, const std::size_t a_y, const Colour& a_col);
        void writeToPNG(const std::string a_file);

        void lookAt(const Vec3& a_target);

        // Creates a primary ray from (sub-)pixel coordinates
        Ray pixelRay(const float a_u, const float a_v) const;
    };

}
