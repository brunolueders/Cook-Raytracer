/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Spherical scene objects                             */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Object.hpp"

namespace cook {

    class Sphere : public Object {
    public:
        Sphere(Material* a_material);

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
