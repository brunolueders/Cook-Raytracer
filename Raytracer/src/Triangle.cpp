#include "Triangle.hpp"

namespace cook {

    Triangle Triangle::unit {
        Vertex{ Vec3{ -.5f, 0.f, -1.f/(2.f*sqrt(3.f)) }, Vec2{ 0.f, 0.f }, Vec3::unitY },
        Vertex{ Vec3{ .5f, 0.f, -1.f/(2.f*sqrt(3.f)) } , Vec2{ 1.f, 0.f }, Vec3::unitY },
        Vertex{ Vec3{ 0.f, 0.f, 1.f/sqrt(3.f) }        , Vec2{ .5f, 1.f }, Vec3::unitY }
    };

    Triangle::Triangle(Vertex a_v0, Vertex a_v1, Vertex a_v2) :
        Shape{ ShapeType::Triangle },
        m_v0{ a_v0 },
        m_v1{ a_v1 },
        m_v2{ a_v2 },
        m_e1{ a_v1.position - m_v0.position },
        m_e2{ a_v2.position - m_v0.position }
    {}

    bool Triangle::intersect(const Ray& a_ray, IntersectionInfo* a_info) {
        // Möller-Trumbore algorithm
        auto e1 = m_v1.position - m_v0.position;
        auto e2 = m_v2.position - m_v0.position;

        auto p = a_ray.direction().cross(e2);
        auto det = e1.dot(p);
        if(det == 0.f) {
            return false;
        }

        auto invDet = 1.f/det;
        auto d = a_ray.origin() - m_v0.position;
        auto u = d.dot(p)*invDet;
        if(u < 0.f || u > 1.f) {
            return false;
        }

        auto q = d.cross(e1);
        auto v = a_ray.direction().dot(q)*invDet;
        if(v < 0.f || u + v > 1.f) {
            return false;
        }

        auto t = e2.dot(q)*invDet;
        if(t > 0.f && t < a_ray.length()) {
            a_info->param = t;
            a_info->point = a_ray.pointAt(t);
            a_info->normal = (1.f - u - v)*m_v0.normal + u*m_v1.normal + v*m_v2.normal;
            return true;
        }
        return false;
    }

    Vertex Triangle::v0() const {
        return m_v0;
    }

    Vertex Triangle::v1() const {
        return m_v1;
    }

    Vertex Triangle::v2() const {
        return m_v2;
    }

}
