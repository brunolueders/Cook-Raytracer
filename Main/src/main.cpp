#include "Raytracer.hpp"
#include <iostream>
#include <fstream>

int main(void) {
    cook::Canvas canvas{ 400, 300 };
    cook::Scene  scene;

    // Attempt to load scene file
    try {
        scene.loadFromStream(std::ifstream("assets/simple.scene.json"), false);
    }
    catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    // Render the scene
    cook::Raytracer renderer{ &canvas, &scene };
    renderer.render("renders/box21.png", 2, 2, 3);
    return 0;
}
