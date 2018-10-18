#include "Transform.hpp"
#include "Util.hpp"

namespace cook {

    Transform::Transform() :
        m_matrix{ Mat44::identity },
        m_invMatrix{ Mat44::identity },
        m_matrixUpdated{ true }
    {}

    Transform::Transform(Transform & a_transform) :
        m_matrixUpdated{ false },
        m_position{ a_transform.m_position },
        m_rotation{ a_transform.m_rotation },
        m_scale{ a_transform.m_scale }
    {}

    Vec3 Transform::pointToWorld(Vec3 a_v) {
        if(!m_matrixUpdated) {
            _updateMatrix();
        }
        return m_matrix.transformPoint(a_v);
    }

    Vec3 Transform::pointToLocal(Vec3 a_v) {
        if(!m_matrixUpdated) {
            _updateMatrix();
        }
        return m_invMatrix.transformPoint(a_v);
    }

    Vec3 Transform::directionToWorld(Vec3 a_v) {
        if(!m_matrixUpdated) {
            _updateMatrix();
        }
        return m_matrix.transformDirection(a_v);
    }

    Vec3 Transform::directionToLocal(Vec3 a_v) {
        if(!m_matrixUpdated) {
            _updateMatrix();
        }
        return m_invMatrix.transformDirection(a_v);
    }

    Vec3 Transform::normalToWorld(Vec3 a_v) {
        if(!m_matrixUpdated) {
            _updateMatrix();
        }
        return m_invMatrix.transpose().transformDirection(a_v).normalize();
    }

    Vec3 Transform::normalToLocal(Vec3 a_v) {
        if(!m_matrixUpdated) {
            _updateMatrix();
        }
        return m_matrix.transpose().transformDirection(a_v).normalize();
    }

    Transform& Transform::translate(const Vec3 a_v) {
        m_position += a_v;
        m_matrixUpdated = false;
        return *this;
    }

    Transform& Transform::rotate(const Vec3 a_v) {
        m_rotation += a_v*PI180;
        m_matrixUpdated = false;
        return *this;
    }

    Transform& Transform::scale(const Vec3 a_v) {
        m_scale += a_v;
        m_matrixUpdated = false;
        return *this;
    }

    Transform& Transform::setPosition(const Vec3 a_v) {
        m_position = a_v;
        m_matrixUpdated = false;
        return *this;
    }

    Transform& Transform::setRotation(const Vec3 a_v) {
        m_rotation = a_v*PI180;
        m_matrixUpdated = false;
        return *this;
    }

    Transform& Transform::setScale(const Vec3 a_v) {
        m_scale = a_v;
        m_matrixUpdated = false;
        return *this;
    }

    Vec3 Transform::position() const {
        return m_position;
    }

    Vec3 Transform::rotation() const {
        return m_rotation;
    }

    Vec3 Transform::scale() const {
        return m_scale;
    }

    Mat44 Transform::matrix() {
        if(!m_matrixUpdated) {
            _updateMatrix();
        }
        return m_matrix;
    }

    Mat44 Transform::invMatrix() {
        if(!m_matrixUpdated) {
            _updateMatrix();
        }
        return m_invMatrix;
    }

    void Transform::_updateMatrix() {
        // Recalculate matrix
        Mat44 scaleMatrix {
            m_scale.x, 0.f,       0.f,        0.f,
            0.f,       m_scale.y, 0.f,        0.f,
            0.f,       0.f,       m_scale.z,  0.f,
            0.f,       0.f,       0.f,        1.f
        };

        Mat44 translMatrix {
            1.f, 0.f, 0.f, m_position.x,
            0.f, 1.f, 0.f, m_position.y,
            0.f, 0.f, 1.f, m_position.z,
            0.f, 0.f, 0.f, 1.f
        };

        auto cosX = std::cos(m_rotation.x), sinX = std::sin(m_rotation.x);
        auto cosY = std::cos(m_rotation.y), sinY = std::sin(m_rotation.y);
        auto cosZ = std::cos(m_rotation.z), sinZ = std::sin(m_rotation.z);
        Mat44 rotMatrix {
            cosY*cosZ, -cosX*sinZ + sinX*sinY*cosZ,  sinX*sinZ + cosX*sinY*cosZ, 0.f,
            cosY*sinZ,  cosX*cosZ + sinX*sinY*sinZ, -sinX*cosZ + cosX*sinY*sinZ, 0.f,
            -sinY,      sinX*cosY,                   cosX*cosY,                  0.f,
            0.f,        0.f,                         0.f,                        1.f
        };

        m_matrix = translMatrix*rotMatrix*scaleMatrix;

        // Recalculate inverse matrix
        scaleMatrix(0, 0) = 1.f/m_scale.x;
        scaleMatrix(1, 1) = 1.f/m_scale.y;
        scaleMatrix(2, 2) = 1.f/m_scale.z;

        translMatrix(0, 3) = -m_position.x;
        translMatrix(1, 3) = -m_position.y;
        translMatrix(2, 3) = -m_position.z;

        m_invMatrix = scaleMatrix*rotMatrix.transpose()*translMatrix;
        m_matrixUpdated = true;
    }
}
