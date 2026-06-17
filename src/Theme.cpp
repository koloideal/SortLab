#include "Theme.hpp"

Theme& Theme::getInstance() {
    static Theme instance;
    return instance;
}

Theme::Theme() : currentTheme_(ThemeType::DARK) {
    initDarkTheme();
    initLightTheme();
    currentPalette_ = &darkPalette_;
}

void Theme::initDarkTheme() {
    // Основные цвета фона
    darkPalette_.windowBackground = sf::Color(10, 12, 20);
    darkPalette_.panelBackground = sf::Color(0, 0, 0, 180);
    darkPalette_.bottomPanelBackground = sf::Color(12, 15, 25);
    darkPalette_.overlayBackground = sf::Color(8, 10, 18, 230);
    
    // Цвета текста
    darkPalette_.textPrimary = sf::Color::White;
    darkPalette_.textSecondary = sf::Color(220, 220, 220);
    darkPalette_.textTertiary = sf::Color(160, 160, 160);
    darkPalette_.textAccent = sf::Color(0, 220, 255);
    
    darkPalette_.stateNormalLow = sf::Color(60, 80, 140);
    darkPalette_.stateNormalHigh = sf::Color(160, 180, 255);
    darkPalette_.stateCompare = sf::Color(0, 220, 255);
    darkPalette_.stateSwap = sf::Color(255, 120, 30);
    darkPalette_.stateSorted = sf::Color(50, 220, 120);
    
    darkPalette_.separator = sf::Color(40, 45, 60);
    darkPalette_.histogramLow = sf::Color(0, 80, 200);
    darkPalette_.histogramHigh = sf::Color(0, 240, 255);
    
    darkPalette_.progressMapNormal = sf::Color(100, 120, 150);
    
    darkPalette_.overlayTitle = sf::Color::White;
    darkPalette_.overlaySubtitle = sf::Color(160, 160, 160);
    darkPalette_.overlaySection = sf::Color(0, 220, 255);
    darkPalette_.overlayBody = sf::Color(200, 200, 200);
    darkPalette_.overlayFooter = sf::Color(100, 100, 100);
    
    darkPalette_.historyTableHeader = sf::Color(0, 220, 255);
    darkPalette_.historyRowEven = sf::Color(0, 0, 0, 0);
    darkPalette_.historyRowOdd = sf::Color(15, 18, 25, 100);
    darkPalette_.historyNewestHighlight = sf::Color(30, 60, 90, 150);
    darkPalette_.historyNewestText = sf::Color(100, 255, 150);
    darkPalette_.historySpeedFastest = sf::Color(100, 255, 120);
    darkPalette_.historySpeedSlow = sf::Color(255, 160, 60);
    
    darkPalette_.statusFinished = sf::Color::Green;
    darkPalette_.statusPlaying = sf::Color::Yellow;
    darkPalette_.statusPaused = sf::Color::White;
}

void Theme::initLightTheme() {
    lightPalette_.windowBackground = sf::Color(245, 247, 250);
    lightPalette_.panelBackground = sf::Color(255, 255, 255, 200);
    lightPalette_.bottomPanelBackground = sf::Color(235, 238, 245);
    lightPalette_.overlayBackground = sf::Color(250, 252, 255, 240);
    
    lightPalette_.textPrimary = sf::Color(20, 20, 30);
    lightPalette_.textSecondary = sf::Color(40, 40, 50);
    lightPalette_.textTertiary = sf::Color(100, 100, 120);
    lightPalette_.textAccent = sf::Color(0, 120, 200);
    
    lightPalette_.stateNormalLow = sf::Color(140, 160, 200);
    lightPalette_.stateNormalHigh = sf::Color(80, 120, 200);
    lightPalette_.stateCompare = sf::Color(0, 180, 255);
    lightPalette_.stateSwap = sf::Color(255, 100, 20);
    lightPalette_.stateSorted = sf::Color(40, 180, 80);
    
    lightPalette_.separator = sf::Color(200, 205, 215);
    lightPalette_.histogramLow = sf::Color(100, 150, 255);
    lightPalette_.histogramHigh = sf::Color(0, 100, 200);
    
    lightPalette_.progressMapNormal = sf::Color(160, 170, 190);
    
    lightPalette_.overlayTitle = sf::Color(20, 20, 30);
    lightPalette_.overlaySubtitle = sf::Color(100, 100, 120);
    lightPalette_.overlaySection = sf::Color(0, 120, 200);
    lightPalette_.overlayBody = sf::Color(40, 40, 50);
    lightPalette_.overlayFooter = sf::Color(140, 140, 150);
    
    lightPalette_.historyTableHeader = sf::Color(0, 120, 200);
    lightPalette_.historyRowEven = sf::Color(0, 0, 0, 0);
    lightPalette_.historyRowOdd = sf::Color(230, 235, 245, 150);
    lightPalette_.historyNewestHighlight = sf::Color(200, 230, 255, 180);
    lightPalette_.historyNewestText = sf::Color(0, 150, 80);
    lightPalette_.historySpeedFastest = sf::Color(40, 180, 80);
    lightPalette_.historySpeedSlow = sf::Color(255, 130, 40);
    
    lightPalette_.statusFinished = sf::Color(0, 150, 60);
    lightPalette_.statusPlaying = sf::Color(200, 150, 0);
    lightPalette_.statusPaused = sf::Color(60, 60, 80);
}

void Theme::setTheme(ThemeType type) {
    currentTheme_ = type;
    currentPalette_ = (type == ThemeType::DARK) ? &darkPalette_ : &lightPalette_;
}

ThemeType Theme::getThemeType() const {
    return currentTheme_;
}

void Theme::toggleTheme() {
    if (currentTheme_ == ThemeType::DARK) {
        setTheme(ThemeType::LIGHT);
    } else {
        setTheme(ThemeType::DARK);
    }
}

const ColorPalette& Theme::getPalette() const {
    return *currentPalette_;
}
