/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Base class for scene objects.                       */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include <memory>
#include "Transform.hpp"
#include "Material.hpp"
#include "Ray.hpp"

namespace cook {

    enum class ObjectType {
        Sphere,
        Rectangle
    };

    class Object {
    private:
        const ObjectType m_type;

    protected:
        Transform m_transform;
        Material* m_material;

    public:
        Object(const ObjectType a_type, Material* a_material);

        ObjectType      type() const;
        Transform&      transform();
        const Material& material() const;

        virtual bool intersect(const Ray& a_ray, IntersectionInfo* a_info) = 0;
    };

}
