#pragma once
#include <SFML/Graphics.hpp>
#include "Sorter.hpp"
#include <string>

class UI {
public:
    UI();
    
    void update(const Sorter& sorter, bool isPlaying, bool isFinished, float stepDelay, const Array& array);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font_;
    sf::Text algorithmText_;
    sf::Text stateText_;
    sf::Text comparisonsText_;
    sf::Text swapsText_;
    sf::Text speedText_;
    sf::Text controlsText_;
    bool fontLoaded_;
};
