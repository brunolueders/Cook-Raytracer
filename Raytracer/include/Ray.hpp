/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Ray and ray intersection data structures.           */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Vec3.hpp"

namespace cook {

    class IntersectionInfo {
    public:
        Vec3   point, normal;
        float  param;
        size_t index;
    };

    class Ray {
    protected:
        Vec3   m_origin;
        Vec3   m_direction;
        float  m_length{ 0.f };
        size_t m_prototype;

    public:
        Ray(const Vec3& a_from, const Vec3& a_to, const size_t a_prototype);
        Ray(const Vec3& a_from, const Vec3& a_dir, const float a_length, const size_t a_prototype);

        Vec3   origin() const;
        Vec3   direction() const;
        float  length() const;
        size_t prototype() const;

        Vec3  pointAt(const float a_t) const;
    };

}
