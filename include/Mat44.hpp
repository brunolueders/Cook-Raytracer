/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* 4x4 Matrix maths                                    */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Vec3.hpp"

namespace cook {

    class Mat44 {
    protected:
        float m_coeffs[4][4];

    public:
        Mat44();
        Mat44(float a_c11, float a_c12, float a_c13, float a_c14, float a_c21, float a_c22,
              float a_c23, float a_c24, float a_c31, float a_c32, float a_c33, float a_c34,
              float a_c41, float a_c42, float a_c43, float a_c44);

        static const Mat44 identity;

        Vec3 transformPoint(const Vec3& a_v);
        Vec3 transformDirection(const Vec3& a_v);

        Mat44 transpose() const;

        Mat44& operator+=(const Mat44& a_b);
        Mat44& operator-=(const Mat44& a_b);
        Mat44& operator*=(const Mat44& a_b);
        Mat44& operator*=(const float a_s);
        Mat44& operator/=(const float a_s);

        Mat44 operator-() const;
        Mat44 operator+(const Mat44& a_b) const;
        Mat44 operator-(const Mat44& a_b) const;
        Mat44 operator*(const Mat44& a_b) const;
        Mat44 operator*(const float a_s) const;
        Mat44 operator/(const float a_s) const;

        bool operator==(const Mat44& a_b) const;
        bool operator!=(const Mat44& a_b) const;

        float& operator()(int a_i, int a_j);

        friend std::ostream& operator<<(std::ostream& a_os, const Mat44& a_m);
    };

    Mat44 operator*(const float a_s, const Mat44& a_m);
}
