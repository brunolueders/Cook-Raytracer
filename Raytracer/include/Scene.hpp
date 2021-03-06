/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Scene management                                    */
/*                                                     */
/* Copyright (c) 2018 Bruno L�ders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Object.hpp"
#include "ResourceMap.hpp"
#include "Rectangle.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "Camera.hpp"

namespace cook {

    class Scene {
    protected:
        MaterialMap          m_materials;
        MeshMap              m_meshes;
        std::vector<Object*> m_objects;
        std::vector<Light>   m_lights;

        Camera m_camera;

        Colour m_ambientLight;
        Colour m_backgroundColour;

    public:
        using ConstLightIterator = std::vector<Light>::const_iterator;

        Scene();
        ~Scene();

        bool closestIntersection(Ray& a_ray, IntersectionInfo* a_info);
        bool doesIntersect(Ray& a_ray);

        void loadFromStream(std::istream& a_stream, bool a_keepCurrentData);

        Object* createMesh(std::string a_meshID, std::string a_materialID);
        Object* createUnitSphere(std::string a_materialID);
        Object* createUnitRectangle(std::string a_materialID);
        Object* createUnitTriangle(std::string a_materialID);
        
        void createLight(Vec3 a_position, float a_radius, Colour a_colour);

        void clear();

        Camera& camera();
        Colour  ambientLight() const;
        Colour  backgroundColour() const;

        ConstLightIterator lightsBegin() const;
        ConstLightIterator lightsEnd() const;

        size_t materialCount() const;
        size_t objectCount() const;
        size_t lightCount() const;
    };

}
