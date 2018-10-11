/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Transform class for easy translation, scaling and   */
/* rotation of coordinates, normals and direction      */
/* vectors.                                            */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Mat44.hpp"

namespace cook{

    /* Keeps data on an object's position, rotation and scale */
    class Transform {
    protected:
        Mat44 m_matrix; // Combined transform matrix (local to world)
        Mat44 m_invMatrix; // Inverse transform matrix (world to local)
        bool  m_matrixUpdated{ false };
        Vec3  m_position, m_rotation, m_scale{ 1.f, 1.f, 1.f };

    public:
        Transform();

        Vec3 pointToWorld(Vec3 a_v);
        Vec3 pointToLocal(Vec3 a_v);
        Vec3 directionToWorld(Vec3 a_v);
        Vec3 directionToLocal(Vec3 a_v);
        Vec3 normalToWorld(Vec3 a_v);
        Vec3 normalToLocal(Vec3 a_v);

        Transform& translate(const Vec3 a_v);
        Transform& rotate(const Vec3 a_v);
        Transform& scale(const Vec3 a_v);

        Transform& setPosition(const Vec3 a_v);
        Transform& setRotation(const Vec3 a_v);
        Transform& setScale(const Vec3 a_v);

        Vec3  position() const;
        Vec3  rotation() const;
        Vec3  scale() const;
        Mat44 matrix();
        Mat44 invMatrix();

    protected:
        void _updateMatrix();
    };

}
