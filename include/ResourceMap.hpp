/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Data structure for managing named resources         */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include <map>
#include "ResourceParsing.hpp"
#include "Material.hpp"

namespace cook {

    template<typename ResourceType>
    class ResourceMap {
    protected:
        std::map<std::string, ResourceType> m_resources;

    public:
        ResourceMap() {}

        void addResources(std::istream& a_stream);

        ResourceType* get(std::string a_name);
    };

    using MaterialMap = ResourceMap<Material>;

}
