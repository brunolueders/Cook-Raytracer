#include "Light.hpp"
#include "Util.hpp"

namespace cook {

    Light::Light(const Vec3 & a_position, const float a_radius, const Colour & a_colour):
        m_position{ a_position },
        m_radius{ a_radius },
        m_colour{ a_colour }
    {}

    Vec3 Light::position() const {
        return m_position;
    }

    float Light::radius() const {
        return m_radius;
    }

    Colour Light::colour() const {
        return m_colour;
    }

    Vec3 Light::sample(const Vec3& a_pos, const Vec3& a_normal, size_t a_prototype) const {
        // Create tangent space coordinate system
        auto lightDir = (m_position - a_pos).normalize();
        auto u = lightDir.cross(a_normal).normalize();
        auto v = lightDir.cross(u).normalize();
        
        // Generate random sample on tangent disc
        auto r = stratifiedSample(a_prototype/3)*m_radius;
        auto theta = stratifiedSample(a_prototype%3)*TWOPI;
        auto x = r*std::cos(theta);
        auto y = r*std::sin(theta);

        // Return Sample point in world coordinates
        return x*u + y*v + m_position;
    }

}
