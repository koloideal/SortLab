#pragma once
#include <SFML/Graphics.hpp>
#include "Sorter.hpp"
#include "SortHistory.hpp"
#include <string>

class UI {
public:
    UI();
    
    void update(const Sorter& sorter, bool isPlaying, bool isFinished, int stepsPerFrame, const Array& array);
    void draw(sf::RenderWindow& window);
    void drawInfoOverlay(sf::RenderWindow& window);
    void drawHistoryOverlay(sf::RenderWindow& window, const SortHistory& history);
    void toggleHistory();
    void closeHistory();
    bool isHistoryOpen() const;

private:
    sf::Font font_;
    sf::Text algorithmText_;
    sf::Text stateText_;
    sf::Text timeComplexityText_;
    sf::Text spaceComplexityText_;
    sf::Text comparisonsText_;
    sf::Text swapsText_;
    sf::Text speedText_;
    sf::Text controlsText_;
    sf::RectangleShape leftBackground_;
    sf::RectangleShape rightBackground_;
    bool fontLoaded_;
    bool historyOpen_;
};
