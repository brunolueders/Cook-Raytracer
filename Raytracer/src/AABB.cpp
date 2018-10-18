#include "AABB.hpp"

namespace cook {

    AABB::AABB() :
        AABB{ Vec3{ -.5f, -.5f, -.5f }, Vec3{ .5f, .5f, .5f }}
    {}

    AABB::AABB(Vec3 a_min, Vec3 a_max) {
        setExtents(a_min, a_max);
    }

    Vec3 AABB::min() const {
        return m_min;
    }

    Vec3 AABB::max() const {
        return m_max;
    }

    void AABB::setExtents(Vec3 a_min, Vec3 a_max) {
        m_min = a_min;
        m_max = a_max;
        m_centre = .5f*(m_max + m_min);
        m_halfExtents = m_max - m_centre;
    }

    bool AABB::intersects(const Ray& a_ray) {
        // Separating-axis test to determine if (not where) the ray
        // interesects the bounding box
        auto m = a_ray.pointAt(a_ray.length()/2.f); // ray mid point
        auto d = m - a_ray.origin(); // ray half length vector

        // Translate to origin
        m -= m_centre;

        // Test world coordinate axes
        auto absDx = abs(d.x);
        if(abs(m.x) > (m_halfExtents.x + absDx)) {
            return false;
        }
        auto absDy = abs(d.y);
        if(abs(m.y) > (m_halfExtents.y + absDy)) {
            return false;
        }
        auto absDz = abs(d.z);
        if(abs(m.z) > (m_halfExtents.z + absDz)) {
            return false;
        }

        // Test axes perpendicular to ray direction and world coordinate axes
        if(abs(m.y*d.z - m.z*d.y) > (m_halfExtents.y*absDz + m_halfExtents.z*absDy)) {
            return false;
        }
        if(abs(m.z*d.x - m.x*d.z) > (m_halfExtents.x*absDz + m_halfExtents.z*absDx)) {
            return false;
        }
        if(abs(m.x*d.y - m.y*d.x) > (m_halfExtents.x*absDy + m_halfExtents.y*absDx)) {
            return false;
        }

        // No separating axis found
        return true;
    }

}
