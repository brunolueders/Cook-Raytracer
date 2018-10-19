/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Surface materials                                   */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include <array>
#include "Ray.hpp"
#include "Canvas.hpp"

namespace cook {

    class Material {
    protected:
        Colour m_ambient, m_diffuse, m_specular, m_transmissive;
        float  m_shininess{ 1.f };
        float  m_translucency{ 1.f };
        float  m_refractiveIndex{ 1.f };
        bool   m_reflective{ false }, m_transparent{ false };

        Canvas* m_texture{ nullptr };

        std::array<float, 10> m_reflectanceFunction{};
        std::array<float, 10> m_transmittanceFunction{};

    public:
        Material(const Colour& a_ambient, const Colour& a_diffuse, const Colour& a_specular,
                 const Colour& a_transmissive, float a_shininess, float a_translucency,
                 float a_refractiveIndex);

        Colour  ambient() const;
        Colour  diffuse() const;
        Colour  specular() const;
        Colour  transmissive() const;
        float   shininess() const;
        float   translucency() const;
        float   refractiveIndex() const;
        Canvas* texture();
        
        // Takes an incident ray and the intersecion normal and returns
        // a random reflection/refraction direction
        Vec3 sampleReflectionFunction(Ray a_ray, Vec3 a_normal) const;
        Vec3 sampleRefractionFunction(Ray a_ray, Vec3 a_normal) const;

        bool isReflective()  const;
        bool isTransparent() const;
        bool isTextured() const;
    };

}
