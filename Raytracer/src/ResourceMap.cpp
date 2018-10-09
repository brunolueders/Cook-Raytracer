#include "ResourceMap.hpp"

namespace cook {

    template<typename ResourceType>
    void ResourceMap<ResourceType>::addResources(std::istream& a_stream) {
        nlohmann::json json;
        a_stream >> json;
        if(json.is_array()) {
            for(auto& elem: json) {
                auto name = elem.at("name").get<std::string>();
                auto ptr = ResourceParsing::parse<ResourceType>(elem);
                m_resources.insert(std::make_pair(name, ptr));
            }
        }
        else {
            auto name = json.at("name").get<std::string>();
            auto ptr = ResourceParsing::parse<ResourceType>(json);
            m_resources.insert(std::make_pair(name, ptr));
        }
    }

    template<typename ResourceType>
    ResourceType* ResourceMap<ResourceType>::get(std::string a_name) {
        auto it = m_resources.find(a_name);
        if(it != m_resources.end()) {
            return &it->second;
        }
        return nullptr;
    }

    template class ResourceMap<Material>;
    template class ResourceMap<Mesh>;

}
