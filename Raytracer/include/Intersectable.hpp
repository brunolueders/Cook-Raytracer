/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Common interface for intersectable objects          */
/*                                                     */
/* Copyright (c) 2018 Bruno L�ders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Ray.hpp"

namespace cook {

    class Intersectable {
    public:
        virtual bool intersect(const Ray& a_ray, IntersectionInfo* a_info) = 0;
    };

}
