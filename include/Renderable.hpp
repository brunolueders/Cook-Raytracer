/*******************************************************/
/* COOK-STYLE RAYTRACER                                */
/*                                                     */
/* Renderables define the shape and material of some-  */
/* thing that can be instantiated in a scene.          */
/*                                                     */
/* Copyright (c) 2018 Bruno Lüders                     */
/* All project code licensed under the MIT license.    */
/*******************************************************/
#pragma once
#include "Intersectable.hpp"
#include "Material.hpp"

namespace cook {

    enum class RenderableType {
        Mesh,
        Sphere,
        Rectangle
    };

    class Renderable : public Intersectable {
    private:
        const RenderableType m_type;

    protected:
        Material* m_material;

    public:
        Renderable(RenderableType a_type, Material* a_material);

        const Material& material() const;
    };

}
