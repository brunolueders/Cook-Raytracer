#include "Raytracer.hpp"

int main(void) {
    cook::Raytracer renderer;
    renderer.init();
    renderer.render();
    return 0;
}
