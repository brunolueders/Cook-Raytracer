/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* 3D vector maths                                     */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include <ostream>

namespace cook {

    class Vec3 {
    public:
        float x{ 0.f }, y{ 0.f }, z{ 0.f };

        static const Vec3 zero;
        static const Vec3 unitX, unitY, unitZ;

        Vec3();
        Vec3(const float a_x, const float a_y, const float a_z);

        float lengthSq() const;
        float length() const;
        float dot(const Vec3& a_b) const;
        Vec3  cross(const Vec3& a_b) const;

        Vec3& normalize();
        Vec3& clamp(const float a_min, const float a_max);
        
        bool closeEnough(const Vec3& a_b, float a_tol);

        Vec3& operator+=(const Vec3& a_b);
        Vec3& operator-=(const Vec3& a_b);
        Vec3& operator*=(const Vec3& a_b);
        Vec3& operator*=(const float a_s);
        Vec3& operator/=(const float a_s);

        Vec3 operator-() const;
        Vec3 operator+(const Vec3& a_b) const;
        Vec3 operator-(const Vec3& a_b) const;
        Vec3 operator*(const Vec3& a_b) const;
        Vec3 operator*(const float a_s) const;
        Vec3 operator/(const float a_s) const;

        bool operator==(const Vec3& a_b) const;
        bool operator!=(const Vec3& a_b) const;

        friend std::ostream& operator<<(std::ostream& a_os, const Vec3& a_v);
    };

    Vec3 operator*(const float a_s, const Vec3& a_v);

    using Colour = Vec3;
}
