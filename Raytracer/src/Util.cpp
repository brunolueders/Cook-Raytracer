#include "Util.hpp"
#include <random>

namespace cook {

    float lerp(float a_ratio, float a_from, float a_to) {
        return ((a_ratio)*a_to + (1.f - a_ratio)*a_from);
    }

    float urand() {
        static std::mt19937 engine{ std::random_device{}() };
        static std::uniform_real_distribution<float> dist;
        return dist(engine);
    }

    float stratifiedSample(size_t a_index) {
        static const auto incr = 1.f/3.f;
        auto jitterMin = a_index*incr;
        return lerp(urand(), jitterMin, jitterMin + incr);
    }

    bool closeEnough(float a_a, float a_b, float a_tol) {
        return abs(a_a - a_b) < a_tol;
    }

}
