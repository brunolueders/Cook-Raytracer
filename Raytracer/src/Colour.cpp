#include "Colour.hpp"
#include <algorithm>

namespace cook {

    const Colour Colour::black{ 0.f, 0.f, 0.f };

    Colour::Colour() {}

    Colour::Colour(const float a_x, const float a_y, const float a_z) :
        r{ a_x },
        g{ a_y },
        b{ a_z }
    {}

    Colour& Colour::clamp() {
        r = std::min(1.f, std::max(0.f, r));
        g = std::min(1.f, std::max(0.f, g));
        b = std::min(1.f, std::max(0.f, b));
        return *this;
    }

    bool Colour::closeEnough(const Colour& a_b, float a_tol) {
        auto absDx = abs(r - a_b.r);
        auto absDy = abs(g - a_b.g);
        auto absDz = abs(b - a_b.b);
        return (absDx < a_tol) && (absDy < a_tol) && (absDz < a_tol);
    }

    Colour& Colour::operator+=(const Colour& a_b) {
        r += a_b.r;
        g += a_b.g;
        b += a_b.b;
        return *this;
    }
    Colour& Colour::operator-=(const Colour& a_b) {
        r -= a_b.r;
        g -= a_b.g;
        b -= a_b.b;
        return *this;
    }
    Colour& Colour::operator*=(const Colour& a_b) {
        r *= a_b.r;
        g *= a_b.g;
        b *= a_b.b;
        return *this;
    }
    Colour& Colour::operator*=(const float a_s) {
        r *= a_s;
        g *= a_s;
        b *= a_s;
        return *this;
    }
    Colour& Colour::operator/=(const float a_s) {
        r /= a_s;
        g /= a_s;
        b /= a_s;
        return *this;
    }

    Colour Colour::operator+(const Colour& a_b) const {
        Colour c{ *this };
        return (c += a_b);
    }
    Colour Colour::operator-(const Colour& a_b) const {
        Colour c{ *this };
        return (c -= a_b);
    }
    Colour Colour::operator*(const Colour& a_b) const {
        Colour c{ *this };
        return (c *= a_b);
    }
    Colour Colour::operator*(const float a_s) const {
        Colour c{ *this };
        return (c *= a_s);
    }
    Colour Colour::operator/(const float a_s) const {
        Colour c{ *this };
        return (c /= a_s);
    }

    bool Colour::operator==(const Colour& a_b) const {
        return ((r == a_b.r) && (g == a_b.g) && (b == a_b.b));
    }

    bool Colour::operator!=(const Colour& a_b) const {
        return ((r != a_b.r) || (g != a_b.g) || (b != a_b.b));
    }

    std::ostream& operator<<(std::ostream& a_os, const Colour& a_v) {
        a_os << '[' << a_v.r << ", " << a_v.g << ", " << a_v.b << ']';
        return a_os;
    }

    Colour operator*(const float a_s, const Colour& a_v) {
        return a_v*a_s;
    }

}
