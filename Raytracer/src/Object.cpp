#include "Object.hpp"

namespace cook {

    Object::Object(Shape* a_shape, Material* a_material) :
        m_shape{ a_shape },
        m_material{ a_material }
    {}

    Shape* Object::shape() {
        return m_shape;
    }

    Material* Object::material() {
        return m_material;
    }

    Transform& Object::transform() {
        return m_transform;
    }

    bool Object::intersect(const Ray& a_ray, IntersectionInfo* a_info) {
        // Transform ray to local coordinate system
        auto localRayOrigin = m_transform.pointToLocal(a_ray.origin());
        auto localRayDir = m_transform.directionToLocal(a_ray.direction());
        Ray localRay{ localRayOrigin, localRayDir, a_ray.length(), a_ray.prototype() };

        if(m_shape->intersect(localRay, a_info)) {
            // Transform intersection info back to world space
            a_info->point = m_transform.pointToWorld(a_info->point);
            a_info->normal = m_transform.normalToWorld(a_info->normal);
            return true;
        }
        return false;
    }

}
