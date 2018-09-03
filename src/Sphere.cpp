#include "Sphere.hpp"
#include "Ray.hpp"

namespace cook {

    Sphere::Sphere(Material* a_material) :
        Object{ ObjectType::Sphere, a_material }
    {}

    bool Sphere::intersect(const Ray& a_ray, IntersectionInfo* a_info) {
        auto rayOrigin    = m_transform.pointToLocal(a_ray.origin());
        auto rayDirection = m_transform.directionToLocal(a_ray.direction());

        auto a = rayOrigin.dot(rayDirection);
        auto b = rayOrigin.lengthSq() - 1.f;
        auto c = rayDirection.lengthSq();
        if((b > 0.f) && (a > 0.f)) {
            return false;
        }

        auto discr = a*a/(c*c) - b/c;
        if(discr < 0.f) {
            return false;
        }

        auto d = std::sqrt(discr);
        auto t = b > 0.f ? -(d + a/c) : (d - a/c);
        if(t < a_ray.length()) {
            auto localPoint = rayOrigin + t*rayDirection;
            a_info->param = t;
            a_info->point = a_ray.pointAt(t);
            a_info->normal = m_transform.normalToWorld(localPoint);
            return true;
        }
        return false;
    }
}
