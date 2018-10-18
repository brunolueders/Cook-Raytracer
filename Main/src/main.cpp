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
    //cook::Canvas canvas{ 200, 150 };
    cook::Canvas canvas{ 800, 600 };
    cook::Scene  scene;

    // Attempt to load scene file
    try {
        scene.loadFromStream(std::ifstream("assets/complex.scene.json"), false);
    }
    catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        std::cin.ignore();
        return 1;
    }

    cook::RaytracerSettings lowSettings;
    cook::RaytracerSettings highSettings;
    highSettings.maxRecursionDepth = 5;
    highSettings.numSubpixels = 4;
    highSettings.numSamplesPerSubpixel = 20;

    // Render the scene
    cook::Raytracer renderer;
    renderer.settings() = highSettings;
    renderer.settings().canvas = &canvas;
    renderer.settings().scene = &scene;

    std::promise<void> stopSignal;
    std::thread progressThread(&outputProgress, stopSignal.get_future(), &renderer);
    auto start = std::chrono::high_resolution_clock::now();

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

    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();
    std::cout << "Elapsed time: ";
    if(elapsedSeconds/60 > 0) {
        std::cout << elapsedSeconds/60 << "m ";
    }
    std::cout << elapsedSeconds%60 << "s" << std::endl;

    canvas.writeToPNG("optimized_render.png");
    std::cin.ignore();
    return 0;
}
