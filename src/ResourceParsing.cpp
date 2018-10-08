#include "ResourceParsing.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

namespace cook {
    namespace ResourceParsing {

        template<>
        Colour parse(nlohmann::json& a_json) {
            auto str = a_json.get<std::string>();
            if(str[0] != '#') {
                throw nlohmann::detail::parse_error::create(101, 0, "unexpected token; expected '#'");
            }

            auto num = std::stoi(str.substr(1), nullptr, 16);
            return Colour{
                static_cast<unsigned char>(num >> 16)/255.f,
                static_cast<unsigned char>(num >> 8)/255.f,
                static_cast<unsigned char>(num)/255.f
            };
        }

        template<>
        Vec2 parse(nlohmann::json& a_json) {
            return Vec2{
                a_json.at(0).get<float>(),
                a_json.at(1).get<float>()
            };
        }

        template<>
        Vec3 parse(nlohmann::json& a_json) {
            return Vec3{
                a_json.at(0).get<float>(),
                a_json.at(1).get<float>(),
                a_json.at(2).get<float>()
            };
        }

        template<>
        Material parse(nlohmann::json& a_json) {
            auto ambient = parse<Colour>(a_json.at("ambient"));
            auto diffuse = parse<Colour>(a_json.at("diffuse"));
            auto specular = parse<Colour>(a_json.at("specular"));
            auto transmissive = parse<Colour>(a_json.at("transmissive"));
            auto shininess = a_json.at("shininess").get<float>();
            auto translucency = a_json.at("translucency").get<float>();
            auto refractiveIndex = a_json.at("refractiveIndex").get<float>();
            return Material{ ambient, diffuse, specular,
                transmissive, shininess, translucency, refractiveIndex };
        }

        template<>
        Vertex parse(nlohmann::json& a_json) {
            auto position = parse<Vec3>(a_json.at("position"));
            auto texCoords = parse<Vec2>(a_json.at("texCoords"));
            auto normal = parse<Vec3>(a_json.at("normal"));
            return Vertex{ position, texCoords, normal };
        }

        template<>
        Triangle parse(nlohmann::json& a_json) {
            auto v0 = parse<Vertex>(a_json.at("v0"));
            auto v1 = parse<Vertex>(a_json.at("v1"));
            auto v2 = parse<Vertex>(a_json.at("v2"));
            return Triangle{ v0, v1, v2 };
        }

        template<>
        Mesh parse(nlohmann::json& a_json) {
            TriangleList tris{};
            for(auto& tri: a_json.at("faces")) {
                tris.push_back(parse<Triangle>(tri));
            }
            return Mesh{ tris };
        }

    }
}
