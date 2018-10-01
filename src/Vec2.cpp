#include "Vec2.hpp"
#include <cmath>
#include <algorithm>

namespace cook {

    const Vec2 Vec2::zero{ 0.f, 0.f };
    const Vec2 Vec2::unitX{ 1.f, 0.f };
    const Vec2 Vec2::unitY{ 0.f, 1.f };

    Vec2::Vec2()
    {}

    Vec2::Vec2(const float a_x, const float a_y) :
        x{ a_x },
        y{ a_y }
    {}

    float Vec2::lengthSq() const {
        return (x*x + y*y);
    }

    float Vec2::length() const {
        return std::sqrt(lengthSq());
    }

    float Vec2::dot(const Vec2& a_b) const {
        return (x*a_b.x + y*a_b.y);
    }

    Vec2& Vec2::normalize() {
        float len = length();
        if(len > 0.f) {
            return operator/=(len);
        }
        return *this;
    }

    Vec2& Vec2::clamp(const float a_min, const float a_max) {
        x = std::min(a_max, std::max(a_min, x));
        y = std::min(a_max, std::max(a_min, y));
        return *this;
    }

    Vec2& Vec2::operator+=(const Vec2& a_b) {
        x += a_b.x;
        y += a_b.y;
        return *this;
    }
    Vec2& Vec2::operator-=(const Vec2& a_b) {
        x -= a_b.x;
        y -= a_b.y;
        return *this;
    }
    Vec2& Vec2::operator*=(const Vec2& a_b) {
        x *= a_b.x;
        y *= a_b.y;
        return *this;
    }
    Vec2& Vec2::operator*=(const float a_s) {
        x *= a_s;
        y *= a_s;
        return *this;
    }
    Vec2& Vec2::operator/=(const float a_s) {
        x /= a_s;
        y /= a_s;
        return *this;
    }

    Vec2 Vec2::operator-() const {
        return Vec2(-x, -y);
    }

    Vec2 Vec2::operator+(const Vec2& a_b) const {
        Vec2 c{ *this };
        return (c += a_b);
    }
    Vec2 Vec2::operator-(const Vec2& a_b) const {
        Vec2 c{ *this };
        return (c -= a_b);
    }
    Vec2 Vec2::operator*(const Vec2& a_b) const {
        Vec2 c{ *this };
        return (c *= a_b);
    }
    Vec2 Vec2::operator*(const float a_s) const {
        Vec2 c{ *this };
        return (c *= a_s);
    }
    Vec2 Vec2::operator/(const float a_s) const {
        Vec2 c{ *this };
        return (c /= a_s);
    }

    bool Vec2::operator==(const Vec2& a_b) const {
        return ((x == a_b.x) && (y == a_b.y));
    }

    bool Vec2::operator!=(const Vec2& a_b) const {
        return ((x != a_b.x) || (y != a_b.y));
    }

    std::ostream& operator<<(std::ostream& a_os, const Vec2& a_v) {
        a_os << '[' << a_v.x << ", " << a_v.y << ']';
        return a_os;
    }

    Vec2 operator*(const float a_s, const Vec2& a_v) {
        return a_v*a_s;
    }

}
