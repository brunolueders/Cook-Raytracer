#include "Sphere.hpp"

namespace cook {

    Sphere::Sphere() :
        Shape{ ShapeType::Sphere }
    {}

    bool Sphere::intersect(const Ray& a_ray, IntersectionInfo* a_info) {
        auto a = a_ray.origin().dot(a_ray.direction());
        auto b = a_ray.origin().lengthSq() - 1.f;
        auto c = a_ray.direction().lengthSq();
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
            a_info->param = t;
            a_info->point = a_ray.pointAt(t);
            a_info->normal = a_info->point; // No need to normalise yet!
            return true;
        }
        return false;
    }
}
