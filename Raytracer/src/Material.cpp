#include "Material.hpp"
#include "Util.hpp"
#include <iostream>
#include <vector>

namespace cook {

    namespace _hemisphereSampling {

        struct _FuncPoint {
            float x, y;
        };

        using _FuncPointList = std::vector<_FuncPoint>;

        /* Calculate Simpson's Rule for reflection distribution function
           cos(x)^exp */
        float _simpson(float a_exp, float a_a, float a_b) {
            auto m = (a_a + a_b)*.5f;
            auto fa = std::pow(std::cos(a_a), a_exp);
            auto fm = std::pow(std::cos(m), a_exp);
            auto fb = std::pow(std::cos(a_b), a_exp);
            return (a_b - a_a)/6.f*(fa + 4.f*fm + fb);
        }

        /* Integrate and invert reflection distribution function using adaptive Simpson's Method */
        void _adaptiveSimpson(float a_exp, float a_a, float a_b, float a_s1, _FuncPointList& a_funcPoints) {
            auto m = (a_a + a_b)*.5f;
            auto s2L = _simpson(a_exp, a_a, m);
            auto s2R = _simpson(a_exp, m, a_b);
            auto s2 = s2L + s2R;
            static const auto h = PI;
            static const auto tol = 1e-6f;

            // Check if desired precision has been reached
            if(std::abs(s2 - a_s1)*h < 15.f*(a_b - a_a)*tol) {
                // Richardson Extrapolation yields slightly better value
                auto extrap = (16.f*s2 - a_s1)/15.f;
                a_funcPoints.push_back(_FuncPoint{ a_funcPoints.back().x + extrap, a_b });
            }
            else {
                // Subdivide
                _adaptiveSimpson(a_exp, a_a, m, s2L, a_funcPoints);
                _adaptiveSimpson(a_exp, m, a_b, s2R, a_funcPoints);
            }
        }

        _FuncPointList _calculateInverseCDF(float a_exp) {
            _FuncPointList invCDF{ _FuncPoint{ 0.f, -HALFPI  } };
            auto s1 = _simpson(a_exp, -HALFPI, HALFPI);
            _adaptiveSimpson(a_exp, -HALFPI, HALFPI, s1, invCDF);
            for(auto& fp : invCDF) {
                // Normalize inverse CDF by dividing through largest value
                fp.x /= invCDF.back().x;
            }
            return invCDF;
        }

        /* Create prototype-indexed reflection/refraction inverse CDF lookup table */
        std::array<float, 10> _createLookupTable(float a_exp) {
            auto invCDF = _calculateInverseCDF(a_exp);
            std::array<float, 10> table{};
            static const auto incr = 1.f/9.f;
            size_t k = 1;
            for(size_t i = 1; i < 5; ++i) {
                auto cur = static_cast<float>(i)*incr;
                for(size_t j = k; j < invCDF.size(); ++j) {
                    if(invCDF[j].x > cur) {
                        auto slope = (invCDF[j].y - invCDF[j-1].y)/(invCDF[j].x - invCDF[j-1].x);
                        table[i] = slope*(cur - invCDF[j-1].x) + invCDF[j-1].y;
                        k = j;
                        break;
                    }
                }
            }

            for(auto i = 0; i < 4; ++i) {
                table[5+i] = -table[4-i];
            }
            table[0] = -HALFPI;
            table[9] = HALFPI;

            return table;
        }

    }

    Material::Material(const Colour & a_ambient, const Colour & a_diffuse, const Colour & a_specular,
                       const Colour & a_transmissive, float a_shininess, float a_translucency,
                       float a_refractiveIndex, std::string a_textureID) :
        m_ambient{a_ambient},
        m_diffuse{a_diffuse},
        m_specular{a_specular},
        m_transmissive{a_transmissive},
        m_shininess{a_shininess},
        m_translucency{a_translucency},
        m_refractiveIndex{a_refractiveIndex},
        m_transparent{ a_transmissive != Colour() },
        m_reflective{ a_specular != Colour{} },
        m_textureID{ a_textureID }
    {
        if(m_reflective) {
            m_reflectanceFunction = _hemisphereSampling::_createLookupTable(m_shininess);
        }

        if(m_transparent) {
            m_transmittanceFunction = _hemisphereSampling::_createLookupTable(m_translucency);
        }
    }

    Colour Material::ambient(Vec2 a_uv) const {
        return isTextured() ? m_ambient*sampleTexture(a_uv) : m_ambient;
    }

    Colour Material::diffuse(Vec2 a_uv) const {
        return isTextured() ? m_diffuse*sampleTexture(a_uv) : m_diffuse;
    }

    Colour Material::specular() const {
        return m_specular;
    }

    Colour Material::transmissive() const {
        return m_transmissive;
    }

    float Material::shininess() const {
        return m_shininess;
    }

    float Material::translucency() const {
        return m_translucency;
    }

    float Material::refractiveIndex() const {
        return m_refractiveIndex;
    }

    std::string Material::textureID() const {
        return m_textureID;
    }

    Canvas* Material::texture() {
        return m_texture;
    }

    void Material::setTexture(Canvas* a_texture) {
        m_texture = a_texture;
    }

    Colour Material::sampleTexture(Vec2 a_uv) const {
        auto x = static_cast<size_t>(a_uv.x*(m_texture->width()-1));
        auto y = static_cast<size_t>((1.f-a_uv.y)*(m_texture->height()-1));
        return m_texture->pixel(x, y);
    }

    Vec3 Material::sampleReflectionFunction(Ray a_ray, Vec3 a_normal) const {
        // Create local coordinate system
        auto reflDir = a_ray.direction() - 2.f*a_normal.dot(a_ray.direction())*a_normal;
        auto u = reflDir.cross(a_normal).normalize();
        auto v = reflDir.cross(u).normalize();

        // Generate random sample on hemisphere
        auto theta = lerp(urand(), m_reflectanceFunction[a_ray.prototype()], m_reflectanceFunction[a_ray.prototype()+1]);
        auto phi = stratifiedSample(a_ray.prototype())*TWOPI;
        auto sinTheta = std::sin(theta), cosTheta = std::cos(theta);
        auto sinPhi = std::sin(phi), cosPhi = std::cos(phi);
        auto x = sinTheta*cosPhi, y = sinTheta*sinPhi, z = cosTheta;

        // Return reflection direction
        return (x*u + y*v + z*reflDir).normalize();
    }

    Vec3 Material::sampleRefractionFunction(Ray a_ray, Vec3 a_normal) const {
        // Figure out if going medium to air or air to medium
        auto dot = a_ray.direction().dot(a_normal);
        auto nratio = m_refractiveIndex;
        if(dot < 0.f) {
            dot = -dot;
            nratio = 1.f/nratio;
        }
        else {
            a_normal = -a_normal;
        }

        auto zeta = 1.f - nratio*nratio*(1.f - dot*dot);
        if(zeta > 0.f) {
            // Create local coordinate system
            auto refrDir = nratio*a_ray.direction() + (nratio*dot - std::sqrt(zeta))*a_normal;
            auto u = refrDir.cross(a_normal).normalize();
            auto v = refrDir.cross(u).normalize();

            // Create random sample on hemisphere
            auto theta = lerp(urand(), m_transmittanceFunction[a_ray.prototype()], m_transmittanceFunction[a_ray.prototype()+1]);
            auto phi = stratifiedSample(a_ray.prototype())*TWOPI;
            auto sinTheta = std::sin(theta), cosTheta = std::cos(theta);
            auto sinPhi = std::sin(phi), cosPhi = std::cos(phi);
            auto x = sinTheta*cosPhi, y = sinTheta*sinPhi, z = cosTheta;

            // Return refraction direction
            return (x*u + y*v + z*refrDir).normalize();
        }
        else {
            // Total reflection, return zero vector
            return Vec3{};
        }
    }

    bool Material::isReflective() const {
        return m_reflective;
    }

    bool Material::isTransparent() const {
        return m_transparent;
    }

    bool Material::isTextured() const {
        return (m_texture != nullptr);
    }

}
