#pragma once
#include "Object.hpp"
#include "ResourceMap.hpp"
#include "Rectangle.hpp"
#include "Sphere.hpp"
#include "Light.hpp"

namespace cook {

    class Scene {
    protected:
        MaterialMap          m_materials;
        MeshMap              m_meshes;
        std::vector<Object*> m_objects;
        std::vector<Light>   m_lights;

    public:
        using ConstLightIterator = std::vector<Light>::const_iterator;

        Scene();
        ~Scene();

        bool closestIntersection(Ray& a_ray, IntersectionInfo* a_info);
        bool doesIntersect(Ray& a_ray);

        Object* createMesh(std::string a_meshID, std::string a_materialID);
        Object* createUnitSphere(std::string a_materialID);
        Object* createUnitRectangle(std::string a_materialID);
        Object* createUnitTriangle(std::string a_materialID);
        
        void createLight(Vec3 a_position, float a_radius, Colour a_colour);

        ConstLightIterator lightsBegin() const;
        ConstLightIterator lightsEnd() const;
    };

}
