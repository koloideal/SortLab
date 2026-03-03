#include "UI.hpp"
#include <iostream>

UI::UI() : fontLoaded_(false) {
    if (!font_.loadFromFile("assets/fonts/JetBrainsMono-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    
    fontLoaded_ = true;
    
    algorithmText_.setFont(font_);
    algorithmText_.setCharacterSize(28);
    algorithmText_.setFillColor(sf::Color::White);
    algorithmText_.setPosition(15.0f, 15.0f);
    
    stateText_.setFont(font_);
    stateText_.setCharacterSize(20);
    stateText_.setFillColor(sf::Color::White);
    stateText_.setPosition(15.0f, 50.0f);
    
    timeComplexityText_.setFont(font_);
    timeComplexityText_.setCharacterSize(16);
    timeComplexityText_.setFillColor(sf::Color(160, 160, 160));
    timeComplexityText_.setPosition(15.0f, 80.0f);
    
    spaceComplexityText_.setFont(font_);
    spaceComplexityText_.setCharacterSize(16);
    spaceComplexityText_.setFillColor(sf::Color(160, 160, 160));
    spaceComplexityText_.setPosition(15.0f, 105.0f);
    
    comparisonsText_.setFont(font_);
    comparisonsText_.setCharacterSize(18);
    comparisonsText_.setFillColor(sf::Color(220, 220, 220));
    comparisonsText_.setPosition(15.0f, 135.0f);
    
    swapsText_.setFont(font_);
    swapsText_.setCharacterSize(18);
    swapsText_.setFillColor(sf::Color(220, 220, 220));
    swapsText_.setPosition(15.0f, 160.0f);
    
    speedText_.setFont(font_);
    speedText_.setCharacterSize(18);
    speedText_.setFillColor(sf::Color(220, 220, 220));
    speedText_.setPosition(15.0f, 185.0f);
    
    controlsText_.setFont(font_);
    controlsText_.setCharacterSize(15);
    controlsText_.setFillColor(sf::Color(200, 200, 200));
    controlsText_.setString("[1-5] Algorithms  [Space] Play/Pause  [Right] Step  [Up/Down] Speed  [R] Shuffle");
    
    leftBackground_.setFillColor(sf::Color(0, 0, 0, 180));
    rightBackground_.setFillColor(sf::Color(0, 0, 0, 180));
}

void UI::update(const Sorter& sorter, bool isPlaying, bool isFinished, int stepsPerFrame, const Array& array) {
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
    
    timeComplexityText_.setString("Time:  " + sorter.getTimeComplexity());
    spaceComplexityText_.setString("Space: " + sorter.getSpaceComplexity());
    
    comparisonsText_.setString("Comparisons: " + std::to_string(array.getComparisons()));
    swapsText_.setString("Swaps: " + std::to_string(array.getSwaps()));
    speedText_.setString("Speed: " + std::to_string(stepsPerFrame) + "x");
}

void UI::draw(sf::RenderWindow& window) {
    if (!fontLoaded_) {
        return;
    }
    
    float leftWidth = 350.0f;
    float leftHeight = 215.0f;
    leftBackground_.setSize(sf::Vector2f(leftWidth, leftHeight));
    leftBackground_.setPosition(5.0f, 5.0f);
    
    sf::FloatRect controlsBounds = controlsText_.getLocalBounds();
    float rightWidth = controlsBounds.width + 20.0f;
    float rightHeight = controlsBounds.height + 20.0f;
    float windowWidth = static_cast<float>(window.getSize().x);
    
    rightBackground_.setSize(sf::Vector2f(rightWidth, rightHeight));
    rightBackground_.setPosition(windowWidth - rightWidth - 5.0f, 5.0f);
    
    controlsText_.setPosition(windowWidth - controlsBounds.width - 15.0f, 15.0f);
    
    window.draw(leftBackground_);
    window.draw(rightBackground_);
    
    window.draw(algorithmText_);
    window.draw(stateText_);
    window.draw(timeComplexityText_);
    window.draw(spaceComplexityText_);
    window.draw(comparisonsText_);
    window.draw(swapsText_);
    window.draw(speedText_);
    window.draw(controlsText_);
}
