#include "stdafx.h"
#include "CppUnitTest.h"
#include "Camera.hpp"
#include "Util.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing {
    TEST_CLASS(Camera) {
    public:

        TEST_METHOD(Camera_PointToWorld) {
            cook::Camera cam{ cook::Vec3{20.f, 20.f, 20.f}, cook::Vec3{}, cook::Vec3::unitY, cook::HALFPI, 1000.f, 1.f, 1.f };
            auto p = cam.pointToWorld(cook::Vec3{ 5.f, -2.f, 1.f });
            Assert::IsTrue(p.closeEnough(cook::Vec3{ 23.7747f, 17.7897f, 16.7036f }, 1e-3f));
        }

        TEST_METHOD(Camera_CalculateFocalPoint) {
            cook::Camera cam{ cook::Vec3{}, -cook::Vec3::unitZ, cook::Vec3::unitY, cook::HALFPI, 1.f, 600.f, 1.f };
            auto f = cam.calculateFocalPoint(cook::Vec3{ 2.f, 2.f, -6.f });
            Assert::IsTrue(f.closeEnough(cook::Vec3{ -200.f, -200.f, -600.f }, 1e-3f));
        }

        TEST_METHOD(Camera_distanceToFarPlane) {
            cook::Camera cam{ cook::Vec3{}, -cook::Vec3::unitZ, cook::Vec3::unitY, cook::HALFPI, 100.f, 10.f, 1.f };
            auto d = cam.distanceToFarPlane(cook::Vec3{ .66667f, .33333f, -.66667f });
            Assert::IsTrue(cook::closeEnough(d, 150.f, 1e-3f));
        }

    };
}
