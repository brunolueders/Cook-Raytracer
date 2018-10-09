/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Parsing of JSON resources (Meshes, Materials, ...)  */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "json.hpp"

namespace cook {
    namespace ResourceParsing {

        template<typename ResType>
        ResType parse(nlohmann::json& a_json);

    }
}
