/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Sub-meshes (a.k.a. triangle groups)                 */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include <vector>
#include "Triangle.hpp"

namespace cook {

    using TriangleList = std::vector<Triangle>;

    class SubMesh : public Intersectable {
    protected:
        TriangleList m_faces;

    public:
        SubMesh(TriangleList a_faces);

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
