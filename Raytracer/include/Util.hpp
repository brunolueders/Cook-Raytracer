/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Utility declarations                                */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
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
}
