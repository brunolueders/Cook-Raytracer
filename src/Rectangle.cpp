#include "Rectangle.hpp"
#include "Ray.hpp"

namespace cook {

    Rectangle::Rectangle(Material * a_material) :
        Object(ObjectType::Rectangle, a_material)
    {}

    bool Rectangle::intersect(const Ray& a_ray, IntersectionInfo * a_info) {
        auto rayOrigin = m_transform.pointToLocal(a_ray.origin());
        auto rayDirection = m_transform.directionToLocal(a_ray.direction());

        auto t = -rayOrigin.y/rayDirection.y;
        if(t > 0.f && t < a_ray.length()) {
            auto x = rayOrigin.x + t*rayDirection.x;
            auto z = rayOrigin.z + t*rayDirection.z;
            if(x < .5f && x > -.5f && z < .5f && z > -.5f) {
                a_info->param = t;
                a_info->point = a_ray.pointAt(t);
                a_info->normal = m_transform.normalToWorld(Vec3::unitY);
                return true;
            }
        }
        return false;
    }

}
