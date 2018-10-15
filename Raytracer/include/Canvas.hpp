/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Drawing canvas                                      */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Colour.hpp"
#include "Vec3.hpp"
#include <vector>

namespace cook {

    class Canvas {
    protected:
        std::vector<Colour> m_pixels;
        std::size_t         m_width{ 0 };
        std::size_t         m_height{ 0 };
        std::size_t         m_size{ 0 }; // width*height
        float               m_aspect{ 0.f };

    public:
        Canvas(std::size_t a_width, std::size_t a_height);

        std::size_t width() const;
        std::size_t height() const;
        std::size_t size() const;
        float       aspect() const;
        Colour      pixel(const std::size_t a_x, const std::size_t a_y) const;

        Vec3 pixelToCamera(float a_u, float a_v, float a_near) const;

        void setPixel(const std::size_t a_x, const std::size_t a_y, const Colour& a_col);
        void writeToPNG(const std::string a_file);
    };

}
