#include "Vertex.hpp"

namespace cook {

    Vertex::Vertex()
    {}

    Vertex::Vertex(Vec3 a_position, Vec2 a_texCoords, Vec3 a_normal):
        position{ a_position },
        texCoords{ a_texCoords },
        normal{ a_normal }
    {}

}
