#include "Mat44.hpp"

namespace cook {

    const Mat44 Mat44::identity {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    };

    Mat44::Mat44() :
        m_coeffs{ 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f }
    {}

    Mat44::Mat44(float a_c11, float a_c12, float a_c13, float a_c14, float a_c21, float a_c22,
                 float a_c23, float a_c24, float a_c31, float a_c32, float a_c33, float a_c34,
                 float a_c41, float a_c42, float a_c43, float a_c44) {
        m_coeffs[0][0] = a_c11; m_coeffs[0][1] = a_c12; m_coeffs[0][2] = a_c13; m_coeffs[0][3] = a_c14;
        m_coeffs[1][0] = a_c21; m_coeffs[1][1] = a_c22; m_coeffs[1][2] = a_c23; m_coeffs[1][3] = a_c24;
        m_coeffs[2][0] = a_c31; m_coeffs[2][1] = a_c32; m_coeffs[2][2] = a_c33; m_coeffs[2][3] = a_c34;
        m_coeffs[3][0] = a_c41; m_coeffs[3][1] = a_c42; m_coeffs[3][2] = a_c43; m_coeffs[3][3] = a_c44;
    }

    Vec3 Mat44::transformPoint(const Vec3 & a_v) {
        return Vec3 {
            a_v.x*m_coeffs[0][0] + a_v.y*m_coeffs[0][1] + a_v.z*m_coeffs[0][2] + m_coeffs[0][3],
            a_v.x*m_coeffs[1][0] + a_v.y*m_coeffs[1][1] + a_v.z*m_coeffs[1][2] + m_coeffs[1][3],
            a_v.x*m_coeffs[2][0] + a_v.y*m_coeffs[2][1] + a_v.z*m_coeffs[2][2] + m_coeffs[2][3]
        };
    }

    Vec3 Mat44::transformDirection(const Vec3 & a_v) {
        return Vec3{
            a_v.x*m_coeffs[0][0] + a_v.y*m_coeffs[0][1] + a_v.z*m_coeffs[0][2],
            a_v.x*m_coeffs[1][0] + a_v.y*m_coeffs[1][1] + a_v.z*m_coeffs[1][2],
            a_v.x*m_coeffs[2][0] + a_v.y*m_coeffs[2][1] + a_v.z*m_coeffs[2][2]
        };
    }

    Mat44 Mat44::transpose() const {
        Mat44 c;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                c.m_coeffs[i][j] = m_coeffs[j][i];
            }
        }
        return c;
    }

    bool Mat44::closeEnough(const Mat44& a_b, float a_tol) const {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                auto diff = m_coeffs[i][j] - a_b.m_coeffs[i][j];
                if(abs(diff) > a_tol) {
                    return false;
                }
            }
        }
        return true;
    }

    Mat44 & Mat44::operator+=(const Mat44 & a_b) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                m_coeffs[i][j] += a_b.m_coeffs[i][j];
            }
        }
        return *this;
    }

    Mat44 & Mat44::operator-=(const Mat44 & a_b) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                m_coeffs[i][j] -= a_b.m_coeffs[i][j];
            }
        }
        return *this;
    }

    Mat44 & Mat44::operator*=(const Mat44 & a_b) {
        Mat44 c;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    c.m_coeffs[i][j] += m_coeffs[i][k]*a_b.m_coeffs[k][j];
                }
            }
        }
        return (*this = c);
    }

    Mat44 & Mat44::operator*=(const float a_s) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                m_coeffs[i][j] *= a_s;
            }
        }
        return *this;
    }

    Mat44 & Mat44::operator/=(const float a_s) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                m_coeffs[i][j] /= a_s;
            }
        }
        return *this;
    }

    Mat44 Mat44::operator-() const {
        Mat44 c;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                c.m_coeffs[i][j] = -m_coeffs[i][j];
            }
        }
        return c;
    }

    Mat44 Mat44::operator+(const Mat44 & a_b) const {
        Mat44 c(*this);
        return (c += a_b);
    }

    Mat44 Mat44::operator-(const Mat44 & a_b) const {
        Mat44 c(*this);
        return (c -= a_b);
    }

    Mat44 Mat44::operator*(const Mat44 & a_b) const {
        Mat44 c(*this);
        return (c *= a_b);
    }

    Mat44 Mat44::operator*(const float a_s) const {
        Mat44 c(*this);
        return (c *= a_s);
    }

    Mat44 Mat44::operator/(const float a_s) const {
        Mat44 c(*this);
        return (c /= a_s);
    }

    bool Mat44::operator==(const Mat44 & a_b) const {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(m_coeffs[i][j] != a_b.m_coeffs[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Mat44::operator!=(const Mat44 & a_b) const {
        return !operator==(a_b);
    }

    float& Mat44::operator()(int a_i, int a_j) {
        return m_coeffs[a_i][a_j];
    }

    std::ostream& operator<<(std::ostream & a_os, const Mat44 & a_m) {
        a_os << "[[" << a_m.m_coeffs[0][0] << ", " << a_m.m_coeffs[0][1] << ", " << a_m.m_coeffs[0][2] << ", " << a_m.m_coeffs[0][3] << "]\n"
             << " [" << a_m.m_coeffs[1][0] << ", " << a_m.m_coeffs[1][1] << ", " << a_m.m_coeffs[1][2] << ", " << a_m.m_coeffs[1][3] << "]\n"
             << " [" << a_m.m_coeffs[2][0] << ", " << a_m.m_coeffs[2][1] << ", " << a_m.m_coeffs[2][2] << ", " << a_m.m_coeffs[2][3] << "]\n"
             << " [" << a_m.m_coeffs[3][0] << ", " << a_m.m_coeffs[3][1] << ", " << a_m.m_coeffs[3][2] << ", " << a_m.m_coeffs[3][3] << "]]";
        return a_os;
    }

    Mat44 operator*(const float a_s, const Mat44 & a_m) {
        return a_m*a_s;
    }

}
