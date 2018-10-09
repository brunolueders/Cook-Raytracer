#include "stdafx.h"
#include "CppUnitTest.h"
#include "Rectangle.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing {
    TEST_CLASS(Intersections) {
    public:
        TEST_METHOD(Rectangle_Intersect) {
            cook::Rectangle rect{};
            cook::Vec3 from{ 1.f, 1.f, 1.f };
            cook::IntersectionInfo info;
            Assert::IsTrue(rect.intersect(cook::Ray{ from, cook::Vec3{ -1.f, -1.f, -.5f }, 0 }, &info));
            Assert::IsTrue(info.point.closeEnough(cook::Vec3{ 0.f, 0.f, .25f }, 1e-6f));
            Assert::IsTrue(info.normal == cook::Vec3::unitY);

            Assert::IsFalse(rect.intersect(cook::Ray{ from, cook::Vec3{ -1.f, -1.f, 1.f }, 0 }, &info));
        }

        TEST_METHOD(Sphere_Intersect) {
            cook::Sphere sphere{};
            cook::Vec3 from{ 1.f, 1.f, 1.f };
            cook::IntersectionInfo info;
            Assert::IsTrue(sphere.intersect(cook::Ray{ from, cook::Vec3{ -1.f, -1.f, -.5f }, 0 }, &info));
            Assert::IsTrue(info.point.closeEnough(cook::Vec3{ .5360973f, .5360973f, .652073f }, 1e-6f));
            Assert::IsTrue(info.normal.closeEnough(cook::Vec3{ .5360973f, .5360973f, .652073f }, 1e-6f));

            Assert::IsFalse(sphere.intersect(cook::Ray{ from, cook::Vec3{ 3.f, -1.f, -.5f }, 0 }, &info));
        }

        TEST_METHOD(Triangle_Intersect) {
            cook::Vertex v0{ cook::Vec3{ -1.f, 2.f, 1.f }, cook::Vec2::zero, cook::Vec3{ 0.f, -1.f, 0.f } };
            cook::Vertex v1{ cook::Vec3{ 2.f, 2.f, -3.f }, cook::Vec2::zero, cook::Vec3{ 1.f, 2.f, 3.f } };
            cook::Vertex v2{ cook::Vec3{ 4.f, -2.f, 1.5f }, cook::Vec2::zero, cook::Vec3{ -1.f, 0.f, -2.f } };
            cook::Triangle tri{ v0, v1, v2 };
            cook::Vec3 from{ 2.f, 0.f, 5.f };
            cook::IntersectionInfo info;
            Assert::IsTrue(tri.intersect(cook::Ray{ from, cook::Vec3{ 1.f, 1.f, -2.f }, 0 }, &info));
            Assert::IsTrue(info.point.closeEnough(cook::Vec3{ 1.32484f, .675159f, .273885f }, 1e-6f));
            Assert::IsTrue(info.normal.closeEnough(cook::Vec3{ -.10828f, 0.f, .00636943f }, 1e-6f));

            Assert::IsFalse(tri.intersect(cook::Ray{ from, cook::Vec3{ -1.f, 0.f, -2.f }, 0 }, &info));
        }
    };
}
