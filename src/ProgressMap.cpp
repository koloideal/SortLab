#include "ProgressMap.hpp"
#include <cmath>

ProgressMap::ProgressMap() {
}

void ProgressMap::draw(sf::RenderWindow& window, const Array& array, sf::Font& font, bool fontLoaded) {
    const float startX = 1066.0f;
    const float startY = 760.0f;
    const float width = 534.0f;
    const float height = 140.0f;
    
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setPosition(startX, startY);
    background.setFillColor(sf::Color(12, 15, 25));
    window.draw(background);
    
    if (fontLoaded) {
        sf::Text label;
        label.setFont(font);
        label.setString("Progress Map");
        label.setCharacterSize(13);
        label.setFillColor(sf::Color(180, 180, 180));
        label.setPosition(startX + 10.0f, startY + 5.0f);
        window.draw(label);
    }
    
    int arraySize = array.getSize();
    int cols = static_cast<int>(std::sqrt(arraySize));
    int rows = (arraySize + cols - 1) / cols;
    
    float availableWidth = width - 20.0f;
    float availableHeight = height - 30.0f;
    
    float squareSizeW = availableWidth / static_cast<float>(cols);
    float squareSizeH = availableHeight / static_cast<float>(rows);
    float squareSize = std::min(squareSizeW, squareSizeH);
    
    if (squareSize < 1.0f) squareSize = 1.0f;
    
    float gridWidth = cols * squareSize;
    float gridHeight = rows * squareSize;
    float offsetX = startX + (width - gridWidth) * 0.5f;
    float offsetY = startY + 30.0f + (availableHeight - gridHeight) * 0.5f;
    
    sf::VertexArray squares(sf::Quads);
    
    for (int i = 0; i < arraySize; ++i) {
        int col = i % cols;
        int row = i / cols;
        
        float x = offsetX + col * squareSize;
        float y = offsetY + row * squareSize;
        
        sf::Color color = getColorForState(array.getState(i));
        
        float gap = 1.0f;
        float actualSize = squareSize - gap;
        
        squares.append(sf::Vertex(sf::Vector2f(x, y), color));
        squares.append(sf::Vertex(sf::Vector2f(x + actualSize, y), color));
        squares.append(sf::Vertex(sf::Vector2f(x + actualSize, y + actualSize), color));
        squares.append(sf::Vertex(sf::Vector2f(x, y + actualSize), color));
    }
    
    window.draw(squares);
}

sf::Color ProgressMap::getColorForState(Array::State state) const {
    switch (state) {
        case Array::State::NORMAL:
            return sf::Color(100, 120, 150);
        case Array::State::COMPARE:
            return sf::Color(0, 220, 255);
        case Array::State::SWAP:
            return sf::Color(255, 120, 30);
        case Array::State::SORTED:
            return sf::Color(50, 220, 120);
        default:
            return sf::Color(100, 120, 150);
    }
}
