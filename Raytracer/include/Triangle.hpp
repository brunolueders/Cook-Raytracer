/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Triangular shapes                                   */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Vertex.hpp"
#include "Shape.hpp"

namespace cook {

    // Represents a triangle with three vertices located anywhere in space
    class Triangle : public Shape {
    protected:
        Vertex m_v0, m_v1, m_v2;
        Vec3   m_e1, m_e2;

    public:
        Triangle(Vertex a_v0, Vertex a_v1, Vertex a_v2);

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    
        Vertex v0() const;
        Vertex v1() const;
        Vertex v2() const;
    };

}
