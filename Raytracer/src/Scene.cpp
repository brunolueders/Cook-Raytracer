#include "Scene.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

namespace cook {

    Scene::Scene()
    {}

    Scene::~Scene() {
        clear();
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

    void Scene::loadFromStream(std::istream& a_stream, bool a_keepCurrentData) {
        if(!a_keepCurrentData) {
            clear();
        }
        nlohmann::json json;
        a_stream >> json;
        
        for(auto& res: json.at("resources")) {
            auto resType = res.at("type").get<std::string>();
            if(resType.compare("material") == 0) {
                if(res.at("data").is_object()) {
                    m_materials.addResources(res.at("data"));
                }
                else {
                    m_materials.addResources(std::ifstream(res.at("data").get<std::string>()));
                }
            }
            else if(resType.compare("mesh") == 0) {
                if(res.at("data").is_object()) {
                    m_meshes.addResources(res.at("data"));
                }
                else {
                    m_meshes.addResources(std::ifstream(res.at("data").get<std::string>()));
                }
            }
        }

        for(auto& light: json.at("lights")) {
            m_lights.push_back(ResourceParsing::parse<Light>(light));
        }

        for(auto& obj: json.at("objects")) {
            auto objType = obj.at("type").get<std::string>();
            auto material = obj.at("material").get<std::string>();
            auto transform = ResourceParsing::parse<Transform>(obj.at("transform"));
            Object* newObj;
            if(objType.compare("rectangle") == 0) {
                newObj = createUnitRectangle(material);
            }
            else if(objType.compare("sphere") == 0) {
                newObj = createUnitSphere(material);
            }
            else if(objType.compare("triangle") == 0) {
                newObj = createUnitTriangle(material);
            }
            else {
                newObj = createMesh(objType, material);
            }

            if(newObj) {
                newObj->transform() = transform;
            }
        }
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

    void Scene::clear() {
        for(auto obj: m_objects) {
            delete obj;
        }
        m_objects.clear();
        m_lights.clear();
        m_materials.clear();
        m_meshes.clear();
    }

    Scene::ConstLightIterator Scene::lightsBegin() const {
        return m_lights.cbegin();
    }

    Scene::ConstLightIterator Scene::lightsEnd() const {
        return m_lights.cend();
    }

    size_t Scene::materialCount() const {
        return m_materials.count();
    }

    size_t Scene::objectCount() const {
        return m_objects.size();
    }

    size_t Scene::lightCount() const {
        return m_lights.size();
    }

}
