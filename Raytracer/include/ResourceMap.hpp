/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Data structure for managing named resources         */
/*                                                     */
/* Copyright (c) 2018 Bruno L�ders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include <map>
#include "ResourceParsing.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

namespace cook {

    template<typename ResourceType>
    class ResourceMap {
    protected:
        std::map<std::string, ResourceType> m_resources;

    public:
        ResourceMap() {}

        void addResources(std::istream& a_stream);
        void addResources(nlohmann::json& a_json);

        ResourceType* get(std::string a_name);

        void clear();

        size_t count() const;
    };

    using MaterialMap = ResourceMap<Material>;
    using MeshMap = ResourceMap<Mesh>;

}
