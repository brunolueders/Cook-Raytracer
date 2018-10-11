#include "Rectangle.hpp"
#include <iostream>

namespace cook {

    Rectangle Rectangle::unit{};

    Rectangle::Rectangle() :
        Shape{ ShapeType::Rectangle }
    {}

    bool Rectangle::intersect(const Ray& a_ray, IntersectionInfo * a_info) {
        auto t = -a_ray.origin().y/a_ray.direction().y;
        if(t > 0.f && t < a_ray.length()) {
            auto x = a_ray.origin().x + t*a_ray.direction().x;
            auto z = a_ray.origin().z + t*a_ray.direction().z;
            if(x < .5f && x > -.5f && z < .5f && z > -.5f) {
                a_info->param = t;
                a_info->point = Vec3{ x, 0.f, z };
                a_info->normal = Vec3::unitY;
                return true;
            }
        }
        return false;
    }

}
