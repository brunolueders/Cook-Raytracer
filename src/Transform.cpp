#include "Transform.hpp"
#include "Util.hpp"

namespace cook {

    Transform::Transform() :
        m_matrix{ Mat44::identity },
        m_invMatrix{ Mat44::identity },
        m_matrixUpdated{ true }
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

    void Transform::translate(const Vec3 a_v) {
        m_position += a_v;
        m_matrixUpdated = false;
    }

    void Transform::rotate(const Vec3 a_v) {
        m_rotation += a_v*PI180;
        m_matrixUpdated = false;
    }

    void Transform::scale(const Vec3 a_v) {
        m_scale += a_v;
        m_matrixUpdated = false;
    }

    void Transform::setPosition(const Vec3 a_v) {
        m_position = a_v;
        m_matrixUpdated = false;
    }

    void Transform::setRotation(const Vec3 a_v) {
        m_rotation = a_v*PI180;
        m_matrixUpdated = false;
    }

    void Transform::setScale(const Vec3 a_v) {
        m_scale = a_v;
        m_matrixUpdated = false;
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

        rotMatrix(0, 1) = cosX*sinZ + sinX*sinY*cosZ;
        rotMatrix(0, 2) = sinX*sinZ - cosX*sinY*cosZ;
        rotMatrix(1, 0) = -cosY*sinZ;
        rotMatrix(1, 1) = cosX*cosZ - sinX*sinY*sinZ;
        rotMatrix(1, 2) = sinX*cosZ + cosX*sinY*sinZ;
        rotMatrix(2, 0) = sinY;
        rotMatrix(2, 1) = -sinX*cosY;

        m_invMatrix = scaleMatrix*rotMatrix.transpose()*translMatrix;
        m_matrixUpdated = true;
    }
}
