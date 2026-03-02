#pragma once
#include <SFML/Graphics.hpp>
#include "Array.hpp"

class App {
public:
    App();
    void run();

private:
    void handleEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window_;
    Array array_;
};
