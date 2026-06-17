#pragma once
#include <SFML/Graphics.hpp>

enum class ThemeType {
    DARK,
    LIGHT
};

struct ColorPalette {
    sf::Color windowBackground;
    sf::Color panelBackground;
    sf::Color bottomPanelBackground;
    sf::Color overlayBackground;
    
    sf::Color textPrimary;
    sf::Color textSecondary;
    sf::Color textTertiary;
    sf::Color textAccent;
    
    sf::Color stateNormalLow;      // Нижняя часть градиента для обычных элементов
    sf::Color stateNormalHigh;     // Верхняя часть градиента для обычных элементов
    sf::Color stateCompare;        // Цвет для сравниваемых элементов
    sf::Color stateSwap;           // Цвет для переставляемых элементов
    sf::Color stateSorted;         // Цвет для отсортированных элементов
    
    sf::Color separator;
    sf::Color histogramLow;        // Нижняя часть градиента гистограммы
    sf::Color histogramHigh;       // Верхняя часть градиента гистограммы
    
    sf::Color progressMapNormal;
    
    sf::Color overlayTitle;
    sf::Color overlaySubtitle;
    sf::Color overlaySection;
    sf::Color overlayBody;
    sf::Color overlayFooter;
    
    sf::Color historyTableHeader;
    sf::Color historyRowEven;
    sf::Color historyRowOdd;
    sf::Color historyNewestHighlight;
    sf::Color historyNewestText;
    sf::Color historySpeedFastest;
    sf::Color historySpeedSlow;
    
    sf::Color statusFinished;
    sf::Color statusPlaying;
    sf::Color statusPaused;
};

class Theme {
public:
    static Theme& getInstance();
    
    void setTheme(ThemeType type);
    ThemeType getThemeType() const;
    void toggleTheme();
    
    const ColorPalette& getPalette() const;
    
private:
    Theme();
    Theme(const Theme&) = delete;
    Theme& operator=(const Theme&) = delete;
    
    void initDarkTheme();
    void initLightTheme();
    
    ThemeType currentTheme_;
    ColorPalette darkPalette_;
    ColorPalette lightPalette_;
    ColorPalette* currentPalette_;
};
