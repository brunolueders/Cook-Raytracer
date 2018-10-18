#include "Mesh.hpp"
#include "Util.hpp"
#include <algorithm>

namespace cook {

    Mesh::Mesh(TriangleList a_triangles) :
        Shape{ ShapeType::Mesh },
        m_triangles{ a_triangles }
    {
        // Calculate AABB
        Vec3 min{ INF, INF, INF }, max{ -INF, -INF, -INF };
        for(auto tri: m_triangles) {
            min.x = std::min(tri.v0().position.x, min.x);
            min.y = std::min(tri.v0().position.y, min.y);
            min.z = std::min(tri.v0().position.z, min.z);

            min.x = std::min(tri.v1().position.x, min.x);
            min.y = std::min(tri.v1().position.y, min.y);
            min.z = std::min(tri.v1().position.z, min.z);

            min.x = std::min(tri.v2().position.x, min.x);
            min.y = std::min(tri.v2().position.y, min.y);
            min.z = std::min(tri.v2().position.z, min.z);

            max.x = std::max(tri.v0().position.x, max.x);
            max.y = std::max(tri.v0().position.y, max.y);
            max.z = std::max(tri.v0().position.z, max.z);

            max.x = std::max(tri.v1().position.x, max.x);
            max.y = std::max(tri.v1().position.y, max.y);
            max.z = std::max(tri.v1().position.z, max.z);

            max.x = std::max(tri.v2().position.x, max.x);
            max.y = std::max(tri.v2().position.y, max.y);
            max.z = std::max(tri.v2().position.z, max.z);
        }
        m_aabb.setExtents(min, max);
    }

    const TriangleList& Mesh::triangles() const {
        return m_triangles;
    }

    bool Mesh::intersect(const Ray& a_ray, IntersectionInfo* a_info) {
        // Test for intersection with the bounding box first
        if(!m_aabb.intersects(a_ray)) {
            return false;
        }

        // Find closest triangle intersected by the ray
        return closestIntersection(m_triangles, a_ray, a_info);
    }

}
