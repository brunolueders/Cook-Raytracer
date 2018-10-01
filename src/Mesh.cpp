#include "Mesh.hpp"

namespace cook {

    Mesh::Mesh(Material* a_material, SubMeshList a_subMeshes) :
        Renderable{ RenderableType::Mesh, a_material },
        m_subMeshes{ a_subMeshes }
    {}

    bool Mesh::intersect(const Ray& a_ray, IntersectionInfo* a_info) {
        // Find closest sub-mesh intersected by the ray
        IntersectionInfo info, closestInfo;
        closestInfo.param = a_ray.length();
        closestInfo.index = m_subMeshes.size();
        for(size_t i = 0; i < m_subMeshes.size(); ++i) {
            if(m_subMeshes[i].intersect(a_ray, &info) && (info.param < closestInfo.param)) {
                closestInfo = info;
                closestInfo.index = i;
            }
        }

        if(closestInfo.index == m_subMeshes.size()) {
            return false;
        }
        *a_info = closestInfo;
        return true;
    }

}
