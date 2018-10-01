/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Mesh vertices                                       */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Vec3.hpp"
#include "Vec2.hpp"

namespace cook {

    class Vertex {
    public:
        Vec3 position;
        Vec2 texCoords;
        Vec3 normal;

    public:
        Vertex();
        Vertex(Vec3 a_position, Vec2 a_texCoords, Vec3 a_normal);
    };

}
