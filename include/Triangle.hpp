/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Triangular shape used by (sub-)meshes               */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Vertex.hpp"
#include "Intersectable.hpp"

namespace cook {

    // Represents a triangle with three vertices located anywhere in space
    class Triangle : public Intersectable {
    protected:
        Vertex m_v0, m_v1, m_v2;
        Vec3   m_e1, m_e2;

    public:
        Triangle(Vertex a_v0, Vertex a_v1, Vertex a_v2);

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
