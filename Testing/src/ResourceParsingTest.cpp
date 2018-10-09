#include "stdafx.h"
#include "CppUnitTest.h"
#include "Triangle.hpp"
#include "ResourceParsing.hpp"
#include "ResourceMap.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing {
    TEST_CLASS(ResourceParsing) {
    public:
        TEST_METHOD(parse_Colour) {
            nlohmann::json j = R"("#31ff08")"_json;
            auto col = cook::ResourceParsing::parse<cook::Colour>(j);
            Assert::IsTrue(col.closeEnough(cook::Colour{ .192f, 1.f, .031f }, 1e-3f));
        
            try {
                nlohmann::json j = R"("445566")"_json;
                cook::ResourceParsing::parse<cook::Colour>(j);
            }
            catch(nlohmann::detail::parse_error&) {
                return;
            }
            Assert::Fail();
        }

        TEST_METHOD(parse_Vec2) {
            nlohmann::json j = R"([1.25, -4.0])"_json;
            auto v = cook::ResourceParsing::parse<cook::Vec2>(j);
            Assert::IsTrue(v == cook::Vec2{ 1.25f, -4.f });
        }

        TEST_METHOD(parse_Vec3) {
            nlohmann::json j = R"([1.25, -4.0, 2])"_json;
            auto v = cook::ResourceParsing::parse<cook::Vec3>(j);
            Assert::IsTrue(v == cook::Vec3{ 1.25f, -4.f, 2.f });
        }

        TEST_METHOD(parse_Material) {
            nlohmann::json j = R"({
                "ambient":"#a5a5a5",
                "diffuse":"#14dd30",
                "specular":"#6f9a5b",
                "transmissive":"#bbaaff",
                "shininess":100.0,
                "translucency":100.0,
                "refractiveIndex":1.25
            })"_json;
            auto mat = cook::ResourceParsing::parse<cook::Material>(j);
            Assert::IsTrue(mat.ambient().closeEnough(cook::Colour{ .647f, .647f, .647f }, 1e-3f));
            Assert::IsTrue(mat.diffuse().closeEnough(cook::Colour{ .078f, .867f, .188f }, 1e-3f));
            Assert::IsTrue(mat.specular().closeEnough(cook::Colour{ .435f, .604f, .357f }, 1e-3f));
            Assert::IsTrue(mat.transmissive().closeEnough(cook::Colour{ .733f, .667f, 1.f }, 1e-3f));
            Assert::IsTrue(mat.shininess() == 100.f);
            Assert::IsTrue(mat.translucency() == 100.f);
            Assert::IsTrue(mat.refractiveIndex() == 1.25f);
        }

        TEST_METHOD(parse_Vertex) {
            nlohmann::json j = R"({
                "position": [ 100, -25, 15.5 ],
                "texCoords": [ 0.25, 0.5 ],
                "normal": [ 0.25, 0.3, -0.1 ]
            })"_json;
            auto v = cook::ResourceParsing::parse<cook::Vertex>(j);
            Assert::IsTrue(v.position == cook::Vec3{ 100.f, -25.f, 15.5f });
            Assert::IsTrue(v.texCoords == cook::Vec2{ .25f, .5f });
            Assert::IsTrue(v.normal == cook::Vec3{ .25f, .3f, -.1f });
        }

        TEST_METHOD(parse_Triangle) {
            nlohmann::json j = R"({
                "v0": {
                    "position": [ -1, 1, 1 ],
                    "texCoords": [ 0, 0 ],
                    "normal": [ 1, 0, 0 ]
                },
                "v1": {
                    "position": [ 1, 1, -1 ],
                    "texCoords": [ 0, 1 ],
                    "normal": [ 0, 1, 0 ]
                },
                "v2": {
                    "position": [ 1, -1, 1 ],
                    "texCoords": [ 1, 0 ],
                    "normal": [ 0, 0, 1 ]
                }
            })"_json;
            auto t = cook::ResourceParsing::parse<cook::Triangle>(j);
            Assert::IsTrue(t.v0().position == cook::Vec3{ -1.f, 1.f, 1.f });
            Assert::IsTrue(t.v1().position == cook::Vec3{ 1.f, 1.f, -1.f });
            Assert::IsTrue(t.v2().position == cook::Vec3{ 1.f, -1.f, 1.f });
        }

        TEST_METHOD(parse_Mesh) {
            nlohmann::json j = R"({
                "faces": [
                    {
                        "v0": {
                            "position": [ -1, 1, 1 ],
                            "texCoords": [ 0, 0 ],
                            "normal": [ 1, 0, 0 ]
                        },
                        "v1": {
                            "position": [ 1, 1, -1 ],
                            "texCoords": [ 0, 1 ],
                            "normal": [ 0, 1, 0 ]
                        },
                        "v2": {
                            "position": [ 1, -1, 1 ],
                            "texCoords": [ 1, 0 ],
                            "normal": [ 0, 0, 1 ]
                        }
                    },
                    {
                        "v0": {
                            "position": [ -1, 1, 1 ],
                            "texCoords": [ 0, 0 ],
                            "normal": [ 1, 0, 0 ]
                        },
                        "v1": {
                            "position": [ 1, 1, -1 ],
                            "texCoords": [ 0, 1 ],
                            "normal": [ 0, 1, 0 ]
                        },
                        "v2": {
                            "position": [ 1, -1, 1 ],
                            "texCoords": [ 1, 0 ],
                            "normal": [ 0, 0, 1 ]
                        }
                    }
                ]
            })"_json;
            auto m = cook::ResourceParsing::parse<cook::Mesh>(j);
            Assert::IsTrue(m.triangles().size() == 2);
        }

        TEST_METHOD(MaterialMap_addResources_Multiple) {
            std::istringstream input(std::string(R"([
                {
                    "name":"shiny",
                    "ambient":"#a5a5a5",
                    "diffuse":"#14dd30",
                    "specular":"#6f9a5b",
                    "transmissive":"#bbaaff",
                    "shininess":100.0,
                    "translucency":100.0,
                    "refractiveIndex":1.25
                },
                {
                    "name":"wood",
                    "ambient":"#a5a5a5",
                    "diffuse":"#14dd30",
                    "specular":"#6f9a5b",
                    "transmissive":"#bbaaff",
                    "shininess":100.0,
                    "translucency":100.0,
                    "refractiveIndex":1.25
                },
                {
                    "name":"copper",
                    "ambient":"#a5a5a5",
                    "diffuse":"#14dd30",
                    "specular":"#6f9a5b",
                    "transmissive":"#bbaaff",
                    "shininess":100.0,
                    "translucency":100.0,
                    "refractiveIndex":1.25
                }
            ])"));
            cook::MaterialMap map{};
            map.addResources(input);
            Assert::IsTrue(map.get("shiny") != nullptr);
            Assert::IsTrue(map.get("wood") != nullptr);
            Assert::IsTrue(map.get("copper") != nullptr);
        }

        TEST_METHOD(MaterialMap_addResources_Single) {
            std::istringstream input(std::string(R"({
                "name":"shiny",
                "ambient":"#a5a5a5",
                "diffuse":"#14dd30",
                "specular":"#6f9a5b",
                "transmissive":"#bbaaff",
                "shininess":100.0,
                "translucency":100.0,
                "refractiveIndex":1.25
            })"));
            cook::MaterialMap map{};
            map.addResources(input);
            Assert::IsTrue(map.get("shiny") != nullptr);
        }
    };
}
