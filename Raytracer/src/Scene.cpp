#include "Scene.hpp"
#include <iostream>
#include <sstream>

namespace cook {

    Scene::Scene() {
        // TODO: DUMMY MATERIALS
        std::istringstream iss(R"([
            { "name":"whiteWall", "ambient":"#e5e5e5", "diffuse":"#e5e5e5", "specular":"#000000", "transmissive":"#000000", "shininess":1, "translucency":1, "refractiveIndex":1},
            { "name":"redWall", "ambient":"#ff6666", "diffuse":"#ff6666", "specular":"#000000", "transmissive":"#000000", "shininess":1, "translucency":1, "refractiveIndex":1},
            { "name":"blueWall", "ambient":"#6666ff", "diffuse":"#6666ff", "specular":"#000000", "transmissive":"#000000", "shininess":1, "translucency":1, "refractiveIndex":1},
            { "name":"frostedGlass", "ambient":"#000000", "diffuse":"#000000", "specular":"#333333", "transmissive":"#ffffff", "shininess":10, "translucency":10, "refractiveIndex":1.05},
            { "name":"purpleMirror", "ambient":"#663399", "diffuse":"#663399", "specular":"#663399", "transmissive":"#000000", "shininess":1000, "translucency":1, "refractiveIndex":1},
            { "name":"blueDiffuse", "ambient":"#4c99cc", "diffuse":"#4c99cc", "specular":"#000000", "transmissive":"#000000", "shininess":1, "translucency":1, "refractiveIndex":1}
        ])");

        try {
            m_materials.addResources(iss);
        }
        catch(std::exception& ex) {
            std::cerr << ex.what() << std::endl;
        }
    }

    Scene::~Scene() {
        for(auto obj: m_objects) {
            delete obj;
        }
    }

    bool Scene::closestIntersection(Ray& a_ray, IntersectionInfo* a_info) {
        return cook::closestIntersection(m_objects, a_ray, a_info);
    }

    bool Scene::doesIntersect(Ray & a_ray) {
        IntersectionInfo dummy;
        for(auto obj: m_objects) {
            if(obj->intersect(a_ray, &dummy)) {
                return true;
            }
        }
        return false;
    }

    Object* Scene::createMesh(std::string a_meshID, std::string a_materialID) {
        auto mesh = m_meshes.get(a_meshID);
        auto material = m_materials.get(a_materialID);
        if(mesh != nullptr && material != nullptr) {
            m_objects.emplace_back(new Object(mesh, material));
            return m_objects.back();
        }
        return nullptr;
    }

    Object* Scene::createUnitSphere(std::string a_materialID) {
        auto material = m_materials.get(a_materialID);
        if(material != nullptr) {
            m_objects.emplace_back(new Object(&Sphere::unit, material));
            return m_objects.back();
        }
        return nullptr;
    }

    Object* Scene::createUnitRectangle(std::string a_materialID) {
        auto material = m_materials.get(a_materialID);
        if(material != nullptr) {
            m_objects.emplace_back(new Object(&Rectangle::unit, material));
            return m_objects.back();
        }
        return nullptr;
    }

    Object* Scene::createUnitTriangle(std::string a_materialID) {
        auto material = m_materials.get(a_materialID);
        if(material != nullptr) {
            m_objects.emplace_back(new Object(&Triangle::unit, material));
            return m_objects.back();
        }
        return nullptr;
    }

    void Scene::createLight(Vec3 a_position, float a_radius, Colour a_colour) {
        m_lights.emplace_back(a_position, a_radius, a_colour);
    }

    const std::vector<Light>& Scene::lights() const {
        return m_lights;
    }

}
