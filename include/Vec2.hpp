/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* 2D vector maths                                     */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include <ostream>

namespace cook {

    class Vec2 {
    public:
        float x{ 0.f }, y{ 0.f };

        static const Vec2 zero;
        static const Vec2 unitX, unitY;

        Vec2();
        Vec2(const float a_x, const float a_y);

        float lengthSq() const;
        float length() const;
        float dot(const Vec2& a_b) const;

        Vec2& normalize();

        Vec2& operator+=(const Vec2& a_b);
        Vec2& operator-=(const Vec2& a_b);
        Vec2& operator*=(const Vec2& a_b);
        Vec2& operator*=(const float a_s);
        Vec2& operator/=(const float a_s);

        Vec2 operator-() const;
        Vec2 operator+(const Vec2& a_b) const;
        Vec2 operator-(const Vec2& a_b) const;
        Vec2 operator*(const Vec2& a_b) const;
        Vec2 operator*(const float a_s) const;
        Vec2 operator/(const float a_s) const;

        bool operator==(const Vec2& a_b) const;
        bool operator!=(const Vec2& a_b) const;

        friend std::ostream& operator<<(std::ostream& a_os, const Vec2& a_v);
    };

    Vec2 operator*(const float a_s, const Vec2& a_v);

}
