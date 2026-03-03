#pragma once
#include <SFML/Graphics.hpp>
#include "Array.hpp"

class ProgressMap {
public:
    ProgressMap();
    
    void draw(sf::RenderWindow& window, const Array& array, sf::Font& font, bool fontLoaded);

private:
    sf::Color getColorForState(Array::State state) const;
};
