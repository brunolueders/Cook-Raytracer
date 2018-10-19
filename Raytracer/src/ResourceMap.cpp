#include "ResourceMap.hpp"

namespace cook {

    template<typename ResourceType>
    void ResourceMap<ResourceType>::addResources(std::istream& a_stream) {
        nlohmann::json json;
        a_stream >> json;
        addResources(json);
    }

    template<typename ResourceType>
    void ResourceMap<ResourceType>::addResources(nlohmann::json& a_json) {
        if(a_json.is_array()) {
            for(auto& elem: a_json) {
                auto name = elem.at("name").get<std::string>();
                auto res = ResourceParsing::parse<ResourceType>(elem);
                m_resources.insert(std::make_pair(name, res));
            }
        }
        else {
            auto name = a_json.at("name").get<std::string>();
            auto res = ResourceParsing::parse<ResourceType>(a_json);
            m_resources.insert(std::make_pair(name, res));
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

    template<typename ResourceType>
    typename ResourceMap<ResourceType>::iterator ResourceMap<ResourceType>::begin() {
        return m_resources.begin();
    }

    template<typename ResourceType>
    typename ResourceMap<ResourceType>::iterator ResourceMap<ResourceType>::end() {
        return m_resources.end();
    }

    template<typename ResourceType>
    void ResourceMap<ResourceType>::clear() {
        m_resources.clear();
    }

    template<typename ResourceType>
    size_t ResourceMap<ResourceType>::count() const {
        return m_resources.size();
    }

    template class ResourceMap<Material>;
    template class ResourceMap<Mesh>;
    template class ResourceMap<Canvas>;

}
