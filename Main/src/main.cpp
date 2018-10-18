#include "Raytracer.hpp"
#include <iostream>
#include <fstream>
#include <thread>
#include <future>

void outputProgress(std::future<void> a_stopSignal, cook::Raytracer* a_renderer) {
    while(a_stopSignal.wait_for(std::chrono::milliseconds(100)) == std::future_status::timeout) {
        std::cout << "Progress: " << std::round(a_renderer->progress()*100.f) << "%\r";
    }
    std::cout << "Progress: 100%" << std::endl;
}

int main(void) {
    cook::Canvas canvas{ 400, 300 };
    cook::Scene  scene;

    // Attempt to load scene file
    try {
        scene.loadFromStream(std::ifstream("assets/simple.scene.json"), false);
    }
    catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        std::cin.ignore();
        return 1;
    }

    // Render the scene
    cook::Raytracer renderer;
    renderer.settings().canvas = &canvas;
    renderer.settings().scene = &scene;

    std::promise<void> stopSignal;
    std::thread progressThread(&outputProgress, stopSignal.get_future(), &renderer);

    try {
        renderer.render();
    }
    catch(std::exception& ex) {
        stopSignal.set_value();
        progressThread.join();
        std::cerr << ex.what() << std::endl;
        std::cin.ignore();
        return 1;
    }

    stopSignal.set_value();
    progressThread.join();

    canvas.writeToPNG("simple1.png");
    return 0;
}
