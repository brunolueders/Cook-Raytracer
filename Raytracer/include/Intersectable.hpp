/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Common interface for intersectable objects          */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Ray.hpp"
#include "Util.hpp"
#include <vector>
#include <type_traits>

namespace cook {

    class Intersectable {
    public:
        virtual bool intersect(const Ray& a_ray, IntersectionInfo* a_info) = 0;
    };

    template<typename T>
    bool closestIntersection(std::vector<T>& a_intersectables, const Ray& a_ray, IntersectionInfo* a_info) {
        static_assert(std::is_base_of<Intersectable, std::remove_pointer_t<T>>(), "Type T must be intersectable!");
        IntersectionInfo cur;
        bool intersects = false;
        a_info->param = a_ray.length();
        for(size_t i = 0; i < a_intersectables.size(); ++i) {
            if(toPointer(a_intersectables[i])->intersect(a_ray, &cur) && cur.param < a_info->param) {
                *a_info = cur;
                intersects = true;
            }
        }
        return intersects;
    }

}
