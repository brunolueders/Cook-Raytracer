#include "Camera.hpp"
#include "Util.hpp"

namespace cook {

    Camera::Camera(const Vec3 & a_position, const Vec3 & a_target, const Vec3 & a_stdup,
                   float a_fov, float a_far, float a_focalLength, float a_aperture) :
        m_position{ a_position },
        m_stdup{ a_stdup },
        m_near{ 1.f/std::tan(a_fov/2.f) },
        m_far{ a_far },
        m_focalLength{ a_focalLength },
        m_aperture{ a_aperture },
        m_fov{ a_fov }
    {
        lookAt(a_target);
    }
    
    Vec3 Camera::position() const {
        return m_position;
    }

    Vec3 Camera::stdUp() const {
        return m_stdup;
    }

    float Camera::focalLength() const {
        return m_focalLength;
    }

    float Camera::aperture() const {
        return m_aperture;
    }

    float Camera::fov() const {
        return m_fov;
    }

    void Camera::lookAt(const Vec3 & a_target) {
        // Calculate the camera's local coordinate system from the
        // default up direction and the target position
        m_look = (a_target - m_position).normalize();
        m_up = (m_stdup - m_look.dot(m_stdup)*m_look).normalize();
        m_right = m_look.cross(m_up).normalize();
    }

    Vec3 Camera::pointToWorld(Vec3 a_v) const {
        return a_v.x*m_right + a_v.y*m_up + a_v.z*m_look + m_position;
    }

    Vec3 Camera::calculateFocalPoint(Vec3 a_rayDirection) const {
        // Calculate the focal point of a ray leaving the camera
        // in a given direction
        return pointToWorld(m_focalLength/a_rayDirection.z*a_rayDirection);
    }

    Vec3 Camera::sampleAperture(std::size_t a_prototype) const {
        // Stratified jittered sampling of the aperture disc
        auto incr = m_aperture*.5f/3.f;
        auto jitterMin = (a_prototype/3)*incr;
        auto r = lerp(urand(), jitterMin, jitterMin + incr);

        incr = TWOPI/3.f;
        jitterMin = (a_prototype%3)*incr;
        auto theta = lerp(urand(), jitterMin, jitterMin + incr);

        return pointToWorld(Vec3 { r*std::cos(theta), r*std::sin(theta), 0.f });
    }

}
