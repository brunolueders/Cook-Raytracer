#include "Renderable.hpp"

namespace cook {

    Renderable::Renderable(RenderableType a_type, Material* a_material) :
        m_type{ a_type },
        m_material{ a_material }
    {}

    const Material& Renderable::material() const {
        return *m_material;
    }
}
