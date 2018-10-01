/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Spherical renderables                               */
/*                                                     */
/* Copyright (c) 2018 Bruno L�ders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Renderable.hpp"

namespace cook {

    class Sphere : public Renderable {
    public:
        Sphere(Material* a_material);

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
