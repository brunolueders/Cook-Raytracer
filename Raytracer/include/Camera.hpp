/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Virtual camera                                      */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Vec3.hpp"

namespace cook {

    class Camera {
    protected:
        Vec3  m_position;
        Vec3  m_stdup; // The standard up direction
        Vec3  m_look, m_right, m_up; // The camera's local coordinate system
        float m_fov;
        float m_near, m_far;
        float m_focalLength;
        float m_aperture;
        
    public:
        Camera();
        Camera(const Vec3& a_position, const Vec3& a_target, const Vec3& a_stdup,
               float a_fov,  float a_far,  float a_focalLength,  float a_aperture);

        Vec3  position() const;
        Vec3  stdUp() const;
        float near() const;
        float far() const;
        float focalLength() const;
        float aperture() const;
        float fov() const;

        void lookAt(const Vec3& a_target);

        Vec3 pointToWorld(Vec3 a_v) const;
        Vec3 calculateFocalPoint(Vec3 a_rayDirection) const;
        Vec3 sampleAperture(std::size_t a_prototype) const;
        
        float distanceToFarPlane(Vec3 a_dir) const;
    };

}
