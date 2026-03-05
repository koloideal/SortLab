#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Array.hpp"
#include "Sorter.hpp"
#include "UI.hpp"
#include "OperationsHistory.hpp"
#include "ProgressMap.hpp"
#include "SortHistory.hpp"

class App {
public:
    App();
    void run();

private:
    void handleEvents();
    void update(float dt);
    void render();
    void renderDeltaHistogram();
    void switchSorter(std::unique_ptr<Sorter> newSorter);
    void generateBeepSound();
    void playBeep(float pitch);

    sf::RenderWindow window_;
    Array array_;
    std::unique_ptr<Sorter> currentSorter_;
    UI ui_;
    OperationsHistory opsHistory_;
    ProgressMap progressMap_;
    bool isPlaying_;
    float timeSinceLastStep_;
    int stepsPerFrame_;
    
    sf::SoundBuffer beepBuffer_;
    sf::Sound beepSound_;
    
    bool isSweeping_;
    int sweepIndex_;
    float sweepTimer_;
    float sweepDelay_;
    
    size_t lastComparisons_;
    size_t lastSwaps_;
    
    sf::Font bottomPanelFont_;
    bool bottomPanelFontLoaded_;
    bool showInfo_;
    
    SortHistory history_;
    sf::Clock sortTimer_;
    bool recordedThisRun_;
};
