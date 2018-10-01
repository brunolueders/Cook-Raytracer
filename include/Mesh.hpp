/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Triangle meshes                                     */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "SubMesh.hpp"
#include "Renderable.hpp"

namespace cook {

    using SubMeshList = std::vector<SubMesh>;

    class Mesh : public Renderable {
    protected:
        SubMeshList m_subMeshes;

    public:
        Mesh(Material* a_material, SubMeshList a_subMeshes);

        bool intersect(const Ray& a_ray, IntersectionInfo* a_info) override;
    };

}
