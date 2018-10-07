/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Base class for shapes of objects.                   */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Intersectable.hpp"

namespace cook {

    enum class ShapeType {
        Mesh,
        Sphere,
        Rectangle,
        Triangle
    };

    class Shape : public Intersectable {
    private:
        const ShapeType m_type;

    public:
        Shape(ShapeType a_type);

        ShapeType type() const;
    };

}
