/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Spherical shapes                                    */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Shape.hpp"

namespace cook {

    // Represents the unit sphere centred at the origin
    class Sphere : public Shape {
    public:
        static Sphere unit;

        Sphere();

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
