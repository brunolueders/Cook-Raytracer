/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Triangle meshes                                     */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include <vector>
#include "Shape.hpp"
#include "Triangle.hpp"
#include "AABB.hpp"

namespace cook {

    using TriangleList = std::vector<Triangle>;

    class Mesh : public Shape {
    protected:
        TriangleList m_triangles;
        AABB         m_aabb;

    public:
        Mesh(TriangleList a_triangles);

        const TriangleList& triangles() const;

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
