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

    class Colour {
    public:
        float r{ 0.f }, g{ 0.f }, b{ 0.f };

        static const Colour black;

        Colour();
        Colour(const float a_r, const float a_g, const float a_b);

        Colour& clamp();

        bool closeEnough(const Colour& a_b, float a_tol);

        Colour& operator+=(const Colour& a_b);
        Colour& operator-=(const Colour& a_b);
        Colour& operator*=(const Colour& a_b);
        Colour& operator*=(const float a_s);
        Colour& operator/=(const float a_s);

        Colour operator+(const Colour& a_b) const;
        Colour operator-(const Colour& a_b) const;
        Colour operator*(const Colour& a_b) const;
        Colour operator*(const float a_s) const;
        Colour operator/(const float a_s) const;

        bool operator==(const Colour& a_b) const;
        bool operator!=(const Colour& a_b) const;

        friend std::ostream& operator<<(std::ostream& a_os, const Colour& a_v);
    };

    Colour operator*(const float a_s, const Colour& a_v);

}
