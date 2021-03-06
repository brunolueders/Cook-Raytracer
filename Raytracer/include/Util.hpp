/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Utility declarations                                */
/*                                                     */
/* Copyright (c) 2018 Bruno L�ders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include <cmath>

namespace cook {

    const static float PI = std::acos(-1.f);
    const static float PI180 = PI/180.f;
    const static float HALFPI = .5f*PI;
    const static float TWOPI = 2.f*PI;

    extern float lerp(float a_ratio, float a_from, float a_to);
    extern float urand();
    extern float stratifiedSample(size_t a_index);

    extern bool closeEnough(float a_a, float a_b, float a_tol);

    template<typename T>
    T* toPointer(T& a_ref) {
        return &a_ref;
    }

    template<typename T>
    T* toPointer(T* a_ptr) {
        return a_ptr;
    }
}
