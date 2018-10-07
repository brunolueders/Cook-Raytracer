#include "Mesh.hpp"

namespace cook {

    Mesh::Mesh(TriangleList a_triangles) :
        Shape{ ShapeType::Mesh },
        m_triangles{ a_triangles }
    {}

    bool Mesh::intersect(const Ray& a_ray, IntersectionInfo* a_info) {
        // Find closest sub-mesh intersected by the ray
        IntersectionInfo info, closestInfo;
        closestInfo.param = a_ray.length();
        closestInfo.index = m_triangles.size();
        for(size_t i = 0; i < m_triangles.size(); ++i) {
            if(m_triangles[i].intersect(a_ray, &info) && (info.param < closestInfo.param)) {
                closestInfo = info;
                closestInfo.index = i;
            }
        }

        if(closestInfo.index == m_triangles.size()) {
            return false;
        }
        *a_info = closestInfo;
        return true;
    }

}
