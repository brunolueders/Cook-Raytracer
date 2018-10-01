/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Scene objects                                       */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Renderable.hpp"
#include "Transform.hpp"

namespace cook {

    /* Scene objects consist of a renderable and a transform.
       The renderable defines the shape and material of
       a kind of object, while the transform places an instance
       of it in the scene. */
    class Object : public Intersectable {
    protected:
        Renderable* m_renderable;
        Transform   m_transform;

    public:
        Object(Renderable* a_renderable);

        Renderable* renderable();
        Transform&  transform();

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
