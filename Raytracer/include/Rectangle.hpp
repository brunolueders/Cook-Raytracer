/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Rectangular flat renderables                        */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Shape.hpp"

namespace cook {

    // Represents the unit rectangle [-0.5,0.5]x[-0.5,0.5] in the xz-plane
    class Rectangle : public Shape {
    public:
        Rectangle();

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
