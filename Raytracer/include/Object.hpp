/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Scene objects                                       */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Shape.hpp"
#include "Transform.hpp"
#include "Material.hpp"

namespace cook {

    /* Scene objects combine a shape with a material
       and a transform. */
    class Object : public Intersectable {
    protected:
        Shape*    m_shape;
        Material* m_material;
        Transform m_transform;

    public:
        Object(Shape* a_shape, Material* a_material);

        Shape*     shape();
        Material*  material();
        Transform& transform();

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
