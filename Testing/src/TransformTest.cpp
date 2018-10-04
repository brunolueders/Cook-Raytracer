#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../include/Transform.hpp"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing {
    TEST_CLASS(Transforms) {
    public:
        TEST_METHOD(Transform_Translate) {
            cook::Transform t;
            t.setPosition(cook::Vec3{ 10.f, -2.5f, 3.f });
            auto matTimesInv = t.matrix()*t.invMatrix();
            Assert::IsTrue(matTimesInv.closeEnough(cook::Mat44::identity, 1e-6f));
        }

        TEST_METHOD(Transform_Rotate) {
            cook::Transform t;
            t.setRotation(cook::Vec3{ 45.f, 20.f, -90.f });
            auto matTimesInv = t.matrix()*t.invMatrix();
            Assert::IsTrue(matTimesInv.closeEnough(cook::Mat44::identity, 1e-6f));
        }

        TEST_METHOD(Transform_Scale) {
            cook::Transform t;
            t.setScale(cook::Vec3{ 3.f, 4.f, 3.f });
            auto matTimesInv = t.matrix()*t.invMatrix();
            Assert::IsTrue(matTimesInv.closeEnough(cook::Mat44::identity, 1e-6f));
        }

        TEST_METHOD(Transform_TranslateRotateScale) {
            cook::Transform t;
            t.setPosition(cook::Vec3{ 10.f, -2.5f, 3.f });
            t.setRotation(cook::Vec3{ 45.f, 20.f, -90.f });
            t.setScale(cook::Vec3{ 3.f, 4.f, 3.f });
            auto matTimesInv = t.matrix()*t.invMatrix();
            Assert::IsTrue(matTimesInv.closeEnough(cook::Mat44::identity, 1e-6f));
        }

        TEST_METHOD(Transform_PointToWorld) {
            cook::Transform t;
            t.setPosition(cook::Vec3{ 10.f, -2.5f, 3.f });
            t.setRotation(cook::Vec3{ 45.f, 20.f, -90.f });
            t.setScale(cook::Vec3{ 3.f, 4.f, 3.f });
            cook::Vec3 v{ 4.f, -2.f, -1.5f };
            Assert::IsTrue(t.pointToWorld(v).closeEnough(cook::Vec3{ 7.52512f, -10.7533f, -9.41003f }, 1e-4f));
        }

        TEST_METHOD(Transform_PointToLocal) {
            cook::Transform t;
            t.setPosition(cook::Vec3{ 10.f, -2.5f, 3.f });
            t.setRotation(cook::Vec3{ 45.f, 20.f, -90.f });
            t.setScale(cook::Vec3{ 3.f, 4.f, 3.f });
            cook::Vec3 v{ 4.f, -2.f, -1.5f };
            Assert::IsTrue(t.pointToLocal(v).closeEnough(cook::Vec3{ .356415f, -1.83841f, .37721f }, 1e-4f));
        }

        TEST_METHOD(Transform_DirectionToWorld) {
            cook::Transform t;
            t.setPosition(cook::Vec3{ 10.f, -2.5f, 3.f });
            t.setRotation(cook::Vec3{ 45.f, 20.f, -90.f });
            t.setScale(cook::Vec3{ 3.f, 4.f, 3.f });
            cook::Vec3 v{ 4.f, -2.f, -1.5f };
            Assert::IsTrue(t.directionToWorld(v).closeEnough(cook::Vec3{ -2.47488f, -8.25326f, -12.41f }, 1e-4f));
        }

        TEST_METHOD(Transform_DirectionToLocal) {
            cook::Transform t;
            t.setPosition(cook::Vec3{ 10.f, -2.5f, 3.f });
            t.setRotation(cook::Vec3{ 45.f, 20.f, -90.f });
            t.setScale(cook::Vec3{ 3.f, 4.f, 3.f });
            cook::Vec3 v{ 4.f, -2.f, -1.5f };
            Assert::IsTrue(t.directionToLocal(v).closeEnough(cook::Vec3{ .797472f, .578856f, -1.11381f }, 1e-4f));
        }

        TEST_METHOD(Transform_NormalToWorld) {
            cook::Transform t;
            t.setPosition(cook::Vec3{ 10.f, -2.5f, 3.f });
            t.setRotation(cook::Vec3{ 45.f, 20.f, -90.f });
            t.setScale(cook::Vec3{ 3.f, 4.f, 3.f });
            cook::Vec3 v{ 4.f, -2.f, -1.5f };
            Assert::IsTrue(t.normalToWorld(v).closeEnough(cook::Vec3{ 0.f, -.66993f, -.742424f }, 1e-4f));
        }

        TEST_METHOD(Transform_NormalToLocal) {
            cook::Transform t;
            t.setPosition(cook::Vec3{ 10.f, -2.5f, 3.f });
            t.setRotation(cook::Vec3{ 45.f, 20.f, -90.f });
            t.setScale(cook::Vec3{ 3.f, 4.f, 3.f });
            cook::Vec3 v{ 4.f, -2.f, -1.5f };
            Assert::IsTrue(t.normalToLocal(v).closeEnough(cook::Vec3{ .465499f, .600626f, -.650081f }, 1e-4f));
        }
    };
}
