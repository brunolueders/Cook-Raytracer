#include "Mesh.hpp"

namespace cook {

    Mesh::Mesh(TriangleList a_triangles) :
        Shape{ ShapeType::Mesh },
        m_triangles{ a_triangles }
    {}

    const TriangleList& Mesh::triangles() const {
        return m_triangles;
    }

    bool Mesh::intersect(const Ray& a_ray, IntersectionInfo* a_info) {
        // Find closest triangle intersected by the ray
        return closestIntersection(m_triangles, a_ray, a_info);
    }

}
