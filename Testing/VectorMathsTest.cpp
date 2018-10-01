#include "stdafx.h"
#include "CppUnitTest.h"
#include "../include/Vec2.hpp"
#include "../include/Vec3.hpp"

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

        TEST_METHOD(Vec2_Clamp) {
            cook::Vec2 v{ 85.f, -20.f };
            Assert::IsTrue(v.clamp(-50.f, 50.f) == cook::Vec2{ 50.f, -20.f });
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

        TEST_METHOD(Vec3_Clamp) {
            cook::Vec3 v{ .85f, 1.2f, -.01f };
            Assert::IsTrue(v.clamp(0.f, 1.f) == cook::Vec3{ .85f, 1.f, 0.f });
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

	};
}
