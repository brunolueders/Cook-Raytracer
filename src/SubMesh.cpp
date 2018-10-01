#include "SubMesh.hpp"

namespace cook {

    SubMesh::SubMesh(TriangleList a_faces) :
        m_faces{ a_faces }
    {}

    bool SubMesh::intersect(const Ray& a_ray, IntersectionInfo* a_info) {
        // Find closest triangle intersected by the ray
        IntersectionInfo info, closestInfo;
        closestInfo.param = a_ray.length();
        closestInfo.index = m_faces.size();
        for(size_t i = 0; i < m_faces.size(); ++i) {
            if(m_faces[i].intersect(a_ray, &info) && (info.param < closestInfo.param)) {
                closestInfo = info;
                closestInfo.index = i;
            }
        }

        if(closestInfo.index == m_faces.size()) {
            return false;
        }
        *a_info = closestInfo;
        return true;
    }

}
