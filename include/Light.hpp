/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Light objects                                       */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Vec3.hpp"

namespace cook {

    class Light {
    protected:
        Vec3   m_position;
        float  m_radius;
        Colour m_colour;

    public:
        Light(const Vec3& a_position, const float a_radius, const Colour& a_colour);

        Vec3   position() const;
        float  radius() const;
        Colour colour() const;

        Vec3 sample(const Vec3& a_pos, const Vec3& a_normal, size_t a_prototype) const;
    };

}
