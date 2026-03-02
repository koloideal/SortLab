#include "App.hpp"

App::App() : window_(sf::VideoMode(1280, 720), "SortLab"), array_(100) {
    window_.setFramerateLimit(60); 
}

void App::run() {
    sf::Clock clock;
    while (window_.isOpen()) {
        float dt = clock.restart().asSeconds();
        handleEvents();
        update(dt);
        render();
    }
}

void App::handleEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            array_.shuffle();
        }
    }
}

void App::update(float dt) {
   
}

void App::render() {
    window_.clear(sf::Color(18, 18, 22)); 

    float width = window_.getSize().x / static_cast<float>(array_.getSize());
    float maxVal = static_cast<float>(array_.getSize());

    for (int i = 0; i < array_.getSize(); ++i) {
        float height = (array_.getValue(i) / maxVal) * (window_.getSize().y * 0.8f);
        
        sf::RectangleShape bar(sf::Vector2f(width - 1.0f, height)); 
        bar.setPosition(i * width, window_.getSize().y - height);   

        switch (array_.getState(i)) {
            case Array::State::NORMAL:  bar.setFillColor(sf::Color(200, 200, 200)); break;
            case Array::State::COMPARE: bar.setFillColor(sf::Color::Yellow); break;
            case Array::State::SWAP:    bar.setFillColor(sf::Color::Red); break;
            case Array::State::SORTED:  bar.setFillColor(sf::Color::Green); break;
        }

        window_.draw(bar);
    }

    window_.display();
}
