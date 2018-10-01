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
#include "Renderable.hpp"
#include "Triangle.hpp"

namespace cook {

    using TriangleList = std::vector<Triangle>;

    class Mesh : public Renderable {
    protected:
        TriangleList m_triangles;

    public:
        Mesh(Material* a_material, TriangleList a_triangles);

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
