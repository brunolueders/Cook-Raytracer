#include "Vec3.hpp"
#include <cmath>
#include <algorithm>

namespace cook {

    const Vec3 Vec3::zero{ 0.f, 0.f, 0.f };
    const Vec3 Vec3::unitX{ 1.f, 0.f, 0.f };
    const Vec3 Vec3::unitY{ 0.f, 1.f, 0.f };
    const Vec3 Vec3::unitZ{ 0.f, 0.f, 1.f };

    Vec3::Vec3()
    {}

    Vec3::Vec3(const float a_x, const float a_y, const float a_z) :
        x{ a_x },
        y{ a_y },
        z{ a_z }
    {}

    float Vec3::lengthSq() const {
        return (x*x + y*y + z*z);
    }

    float Vec3::length() const {
        return std::sqrt(lengthSq());
    }

    float Vec3::dot(const Vec3& a_b) const {
        return (x*a_b.x + y*a_b.y + z*a_b.z);
    }

    Vec3 Vec3::cross(const Vec3& a_b) const {
        return Vec3(y*a_b.z - z*a_b.y,
                    z*a_b.x - x*a_b.z,
                    x*a_b.y - y*a_b.x);
    }

    Vec3& Vec3::normalize() {
        float len = length();
        if(len > 0.f) {
            return operator/=(len);
        }
        return *this;
    }

    Vec3& Vec3::clamp(const float a_min, const float a_max) {
        x = std::min(a_max, std::max(a_min, x));
        y = std::min(a_max, std::max(a_min, y));
        z = std::min(a_max, std::max(a_min, z));
        return *this;
    }

    Vec3& Vec3::operator+=(const Vec3& a_b) {
        x += a_b.x;
        y += a_b.y;
        z += a_b.z;
        return *this;
    }
    Vec3& Vec3::operator-=(const Vec3& a_b) {
        x -= a_b.x;
        y -= a_b.y;
        z -= a_b.z;
        return *this;
    }
    Vec3& Vec3::operator*=(const Vec3& a_b) {
        x *= a_b.x;
        y *= a_b.y;
        z *= a_b.z;
        return *this;
    }
    Vec3& Vec3::operator*=(const float a_s) {
        x *= a_s;
        y *= a_s;
        z *= a_s;
        return *this;
    }
    Vec3& Vec3::operator/=(const float a_s) {
        x /= a_s;
        y /= a_s;
        z /= a_s;
        return *this;
    }

    Vec3 Vec3::operator-() const {
        return Vec3(-x, -y, -z);
    }

    Vec3 Vec3::operator+(const Vec3& a_b) const {
        Vec3 c{ *this };
        return (c += a_b);
    }
    Vec3 Vec3::operator-(const Vec3& a_b) const {
        Vec3 c{ *this };
        return (c -= a_b);
    }
    Vec3 Vec3::operator*(const Vec3& a_b) const {
        Vec3 c{ *this };
        return (c *= a_b);
    }
    Vec3 Vec3::operator*(const float a_s) const {
        Vec3 c{ *this };
        return (c *= a_s);
    }
    Vec3 Vec3::operator/(const float a_s) const {
        Vec3 c{ *this };
        return (c /= a_s);
    }

    bool Vec3::operator==(const Vec3& a_b) const {
        return ((x == a_b.x) && (y == a_b.y) && (z == a_b.z));
    }

    bool Vec3::operator!=(const Vec3& a_b) const {
        return ((x != a_b.x) || (y != a_b.y) || (z != a_b.z));
    }

    std::ostream& operator<<(std::ostream& a_os, const Vec3& a_v) {
        a_os << '[' << a_v.x << ", " << a_v.y << ", " << a_v.z << ']';
        return a_os;
    }

    Vec3 operator*(const float a_s, const Vec3& a_v) {
        return a_v*a_s;
    }

}
