#pragma once
#include "Vec3.hpp"
#include "Intersectable.hpp"

namespace cook {

    class AABB {
    protected:
        Vec3 m_min;
        Vec3 m_max;
        Vec3 m_centre;
        Vec3 m_halfExtents;

    public:
        AABB();
        AABB(Vec3 a_min, Vec3 a_max);

        Vec3 min() const;
        Vec3 max() const;

        void setExtents(Vec3 a_min, Vec3 a_max);

        bool intersects(const Ray& a_ray);
    };

}
