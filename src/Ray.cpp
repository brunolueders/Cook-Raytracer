#include "Ray.hpp"

namespace cook {

    Ray::Ray(const Vec3& a_from, const Vec3& a_to, const size_t a_prototype) :
        m_origin{ a_from },
        m_direction{ a_to - a_from },
        m_prototype{ a_prototype }
    {
        m_length = m_direction.length();
        if(m_length > 0.f) {
            m_direction /= m_length;
        }
    }

    Ray::Ray(const Vec3& a_from, const Vec3& a_dir, const float a_length, const size_t a_prototype) :
        m_origin{ a_from },
        m_direction{ a_dir },
        m_length{ a_length },
        m_prototype{ a_prototype }
    {}

    Vec3 Ray::origin() const {
        return m_origin;
    }

    Vec3 Ray::direction() const {
        return m_direction;
    }

    float Ray::length() const {
        return m_length;
    }

    size_t Ray::prototype() const {
        return m_prototype;
    }

    Vec3 Ray::pointAt(const float a_t) const {
        return (m_origin + a_t*m_direction);
    }

}
