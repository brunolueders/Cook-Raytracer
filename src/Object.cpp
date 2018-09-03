#include "Object.hpp"

namespace cook {

    Object::Object(const ObjectType a_type, Material* a_material) :
        m_type{ a_type },
        m_material{ a_material }
    {}

    ObjectType Object::type() const {
        return m_type;
    }

    Transform & Object::transform() {
        return m_transform;
    }

    const Material& Object::material() const {
        return *m_material;
    }

}
