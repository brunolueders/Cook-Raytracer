#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../include/Vec2.hpp"
#include "../../include/Vec3.hpp"
#include "../../include/Mat44.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing {		
	TEST_CLASS(VectorMaths) {
	public:
		TEST_METHOD(Vec2_Length) {
            cook::Vec2 v{ 4.f, -3.f };
            Assert::AreEqual(v.lengthSq(), 25.f);
            Assert::AreEqual(v.length(), 5.f);
		}

        TEST_METHOD(Vec2_Dot) {
            cook::Vec2 v{ -2.5f, 1.f };
            cook::Vec2 u{ 2.f, -.5f };
            Assert::AreEqual(v.dot(u), -5.5f);
        }

        TEST_METHOD(Vec2_Arithmetic) {
            cook::Vec2 v{ 0.f, -2.f };
            cook::Vec2 u{ 1.f, 4.f };
            Assert::IsTrue(v + u == cook::Vec2{ 1.f, 2.f });
            Assert::IsTrue(v - u == cook::Vec2{ -1.f, -6.f });
            Assert::IsTrue(v * u == cook::Vec2{ 0.f, -8.f });
            Assert::IsTrue(u * 3.f == cook::Vec2{ 3.f, 12.f });
            Assert::IsTrue(u / 2.f == cook::Vec2{ .5f, 2.f });
        }

        TEST_METHOD(Vec3_Length) {
            cook::Vec3 v{ 2.f, 4.f, -4.f };
            Assert::AreEqual(v.lengthSq(), 36.f);
            Assert::AreEqual(v.length(), 6.f);
        }

        TEST_METHOD(Vec3_Dot) {
            cook::Vec3 v{ 0.f, -10.f, 6.f };
            cook::Vec3 u{ 24.f, -.5f, -1.f };
            Assert::AreEqual(v.dot(u), -1.f);
        }

        TEST_METHOD(Vec3_Cross) {
            cook::Vec3 v{ 2.f, 1.f, 4.f };
            cook::Vec3 u{ -1.f, 0.f, 0.f };
            Assert::IsTrue(v.cross(u) == cook::Vec3{ 0.f, -4.f, 1.f });
        }

        TEST_METHOD(Vec3_CloseEnough) {
            cook::Vec3 v{ 2.f, 0.f, -1.f };
            cook::Vec3 u{ 2.f, -0.001f, -0.999f };
            Assert::IsTrue(v.closeEnough(u, 1e-2f));
            Assert::IsFalse(v.closeEnough(u, 1e-4f));
        }

        TEST_METHOD(Vec3_Arithmetic) {
            cook::Vec3 v{ 2.f, -2.f, 1.f };
            cook::Vec3 u{ 4.f, 10.f, 4.75f };
            Assert::IsTrue(v + u == cook::Vec3{ 6.f, 8.f, 5.75f });
            Assert::IsTrue(v - u == cook::Vec3{ -2.f, -12.f, -3.75f });
            Assert::IsTrue(v * u == cook::Vec3{ 8.f, -20.f, 4.75f });
            Assert::IsTrue(u * 2.f == cook::Vec3{ 8.f, 20.f, 9.5f });
            Assert::IsTrue(v / -4.f == cook::Vec3{ -.5f, .5f, -.25f });
        }

        TEST_METHOD(Mat44_Transform) {
            cook::Mat44 m {
                1.f, -2.f, 4.f, 1.f,
                0.f, .5f, -3.f, 0.f,
                1.5f, 2.f, 1.f, -1.f,
                4.f, 6.f, 2.f, .5f
            };
            cook::Vec3 v{ 1.f, -2.f, 1.5f };
            Assert::IsTrue(m.transformPoint(v) == cook::Vec3{ 12.f, -5.5f, -2.f });
            Assert::IsTrue(m.transformDirection(v) == cook::Vec3{ 11.f, -5.5f, -1.f });
        }

        TEST_METHOD(Mat44_Transpose) {
            cook::Mat44 m {
                1.f, -2.f, 4.f, 1.f,
                0.f, .5f, -3.f, 0.f,
                1.5f, 2.f, 1.f, -1.f,
                4.f, 6.f, 2.f, .5f
            };
            cook::Mat44 expected {
                1.f, 0.f, 1.5f, 4.f,
                -2.f, .5f, 2.f, 6.f,
                4.f, -3.f, 1.f, 2.f,
                1.f, 0.f, -1.f, .5f
            };
            Assert::IsTrue(m.transpose() == expected);
        }

        TEST_METHOD(Mat44_CloseEnough) {
            cook::Mat44 m {
                1.f, -2.f, 4.f, 1.f,
                0.f, .5f, -3.f, 0.f,
                1.5f, 2.f, 1.f, -1.f,
                4.f, 6.f, 2.f, .5f
            };
            cook::Mat44 n {
                1.001f, -2.001f, 4.f, 1.f,
                0.f, .5f, -3.001f, 0.f,
                1.5f, 2.001f, 1.f, -1.f,
                3.999f, 6.f, 2.001f, .5f
            };
            Assert::IsTrue(m.closeEnough(n, 1e-2f));
            Assert::IsFalse(m.closeEnough(n, 1e-4f));
        }

        TEST_METHOD(Mat44_Arithmetic) {
            cook::Mat44 m {
                2.f, -1.f, 0.f, 4.f,
                .5f, 1.f, -4.f, 2.f,
                3.f, 3.f, 1.f, 0.f,
                2.f, 0.f, 0.f, 2.f
            };
            cook::Mat44 n {
                1.f, 1.f, -1.f, -1.f,
                2.f, 4.f, 1.f, 0.f,
                0.f, 0.f, -2.f, 1.f,
                4.f, 0.f, -4.f, -4.f
            };
            Assert::IsTrue(m + n == cook::Mat44 {
                3.f, 0.f, -1.f, 3.f,
                2.5f, 5.f, -3.f, 2.f,
                3.f, 3.f, -1.f, 1.f,
                6.f, 0.f, -4.f, -2.f
            });
            Assert::IsTrue(m - n == cook::Mat44 {
                1.f, -2.f, 1.f, 5.f,
                -1.5, -3.f, -5.f, 2.f,
                3.f, 3.f, 3.f, -1.f,
                -2.f, 0.f, 4.f, 6.f
            });
            Assert::IsTrue(m*n == cook::Mat44 {
                16.f, -2.f, -19.f, -18.f,
                10.5f, 4.5f, .5f, -12.5f,
                9.f, 15.f, -2.f, -2.f,
                10.f, 2.f, -10.f, -10.f
            });
            Assert::IsTrue(m*2.f == cook::Mat44 {
                4.f, -2.f, 0.f, 8.f,
                1.f, 2.f, -8.f, 4.f,
                6.f, 6.f, 2.f, 0.f,
                4.f, 0.f, 0.f, 4.f
            });
            Assert::IsTrue(n/2.f == cook::Mat44 {
                .5f, .5f, -.5f, -.5f,
                1.f, 2.f, .5f, 0.f,
                0.f, 0.f, -1.f, .5f,
                2.f, 0.f, -2.f, -2.f
            });
        }

	};
}
