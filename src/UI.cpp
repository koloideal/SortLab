#include "UI.hpp"
#include <iostream>

UI::UI() : fontLoaded_(false) {
    if (!font_.loadFromFile("assets/fonts/Roboto-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    
    fontLoaded_ = true;
    
    algorithmText_.setFont(font_);
    algorithmText_.setCharacterSize(24);
    algorithmText_.setFillColor(sf::Color::White);
    algorithmText_.setPosition(20.0f, 20.0f);
    
    stateText_.setFont(font_);
    stateText_.setCharacterSize(20);
    stateText_.setFillColor(sf::Color::White);
    stateText_.setPosition(20.0f, 55.0f);
    
    comparisonsText_.setFont(font_);
    comparisonsText_.setCharacterSize(18);
    comparisonsText_.setFillColor(sf::Color(200, 200, 200));
    comparisonsText_.setPosition(20.0f, 90.0f);
    
    swapsText_.setFont(font_);
    swapsText_.setCharacterSize(18);
    swapsText_.setFillColor(sf::Color(200, 200, 200));
    swapsText_.setPosition(20.0f, 115.0f);
    
    speedText_.setFont(font_);
    speedText_.setCharacterSize(18);
    speedText_.setFillColor(sf::Color(200, 200, 200));
    speedText_.setPosition(20.0f, 140.0f);
    
    controlsText_.setFont(font_);
    controlsText_.setCharacterSize(14);
    controlsText_.setFillColor(sf::Color(150, 150, 150));
    controlsText_.setPosition(20.0f, 175.0f);
    controlsText_.setString("[1-5] Algorithms  [Space] Play/Pause  [Right] Step  [Up/Down] Speed  [R] Shuffle");
}

void UI::update(const Sorter& sorter, bool isPlaying, bool isFinished, float stepDelay, const Array& array) {
    if (!fontLoaded_) {
        return;
    }
    
    algorithmText_.setString("Algorithm: " + sorter.getName());
    
    std::string state;
    if (isFinished) {
        state = "Status: Finished";
        stateText_.setFillColor(sf::Color::Green);
    } else if (isPlaying) {
        state = "Status: Playing";
        stateText_.setFillColor(sf::Color::Yellow);
    } else {
        state = "Status: Paused";
        stateText_.setFillColor(sf::Color::White);
    }
    stateText_.setString(state);
    
    comparisonsText_.setString("Comparisons: " + std::to_string(array.getComparisons()));
    swapsText_.setString("Swaps: " + std::to_string(array.getSwaps()));
    
    int delayMs = static_cast<int>(stepDelay * 1000.0f);
    speedText_.setString("Delay: " + std::to_string(delayMs) + "ms");
}

void UI::draw(sf::RenderWindow& window) {
    if (!fontLoaded_) {
        return;
    }
    
    window.draw(algorithmText_);
    window.draw(stateText_);
    window.draw(comparisonsText_);
    window.draw(swapsText_);
    window.draw(speedText_);
    window.draw(controlsText_);
}
