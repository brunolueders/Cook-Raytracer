#include "Shape.hpp"

namespace cook {

    Shape::Shape(ShapeType a_type) :
        m_type{ a_type }
    {}

    ShapeType Shape::type() const {
        return m_type;
    }

}
