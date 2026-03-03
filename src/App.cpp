#include "App.hpp"
#include "sorters/BubbleSorter.hpp"
#include "sorters/SelectionSorter.hpp"
#include "sorters/InsertionSorter.hpp"
#include "sorters/MergeSorter.hpp"
#include "sorters/QuickSorter.hpp"

App::App() 
    : window_(sf::VideoMode(1600, 900), "SortLab")
    , array_(100)
    , currentSorter_(std::make_unique<BubbleSorter>())
    , ui_()
    , opsHistory_(300)
    , isPlaying_(false)
    , timeSinceLastStep_(0.0f)
    , stepsPerFrame_(1)
    , isSweeping_(false)
    , sweepIndex_(0)
    , sweepTimer_(0.0f)
    , sweepDelay_(0.005f)
    , lastComparisons_(0)
    , lastSwaps_(0)
    , histogramFontLoaded_(false) {
    window_.setFramerateLimit(60);
    generateBeepSound();
    beepSound_.setBuffer(beepBuffer_);
    beepSound_.setVolume(100.0f);
    
    if (histogramFont_.loadFromFile("assets/fonts/JetBrainsMono-Regular.ttf")) {
        histogramFontLoaded_ = true;
    }
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
        
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Space:
                    isPlaying_ = !isPlaying_;
                    break;
                    
                case sf::Keyboard::Right:
                    if (!isPlaying_ && !currentSorter_->isFinished()) {
                        currentSorter_->step(array_);
                    }
                    break;
                    
                case sf::Keyboard::Up:
                    stepsPerFrame_ = (stepsPerFrame_ < 500) ? stepsPerFrame_ * 2 : 500;
                    if (stepsPerFrame_ < 1) stepsPerFrame_ = 1;
                    break;
                    
                case sf::Keyboard::Down:
                    stepsPerFrame_ = (stepsPerFrame_ > 1) ? stepsPerFrame_ / 2 : 1;
                    if (stepsPerFrame_ < 1) stepsPerFrame_ = 1;
                    break;
                    
                case sf::Keyboard::Num1:
                    switchSorter(std::make_unique<BubbleSorter>());
                    break;
                    
                case sf::Keyboard::Num2:
                    switchSorter(std::make_unique<SelectionSorter>());
                    break;
                    
                case sf::Keyboard::Num3:
                    switchSorter(std::make_unique<InsertionSorter>());
                    break;
                    
                case sf::Keyboard::Num4:
                    switchSorter(std::make_unique<MergeSorter>());
                    break;
                    
                case sf::Keyboard::Num5:
                    switchSorter(std::make_unique<QuickSorter>());
                    break;
                    
                case sf::Keyboard::R:
                    array_.shuffle();
                    array_.resetStates();
                    array_.resetCounters();
                    currentSorter_->reset();
                    opsHistory_.reset();
                    isPlaying_ = false;
                    timeSinceLastStep_ = 0.0f;
                    isSweeping_ = false;
                    sweepIndex_ = 0;
                    lastComparisons_ = 0;
                    lastSwaps_ = 0;
                    stepsPerFrame_ = 1;
                    break;
                    
                case sf::Keyboard::Q:
                    window_.close();
                    break;
                    
                default:
                    break;
            }
        }
    }
}

void App::update(float dt) {
    ui_.update(*currentSorter_, isPlaying_, currentSorter_->isFinished(), stepsPerFrame_, array_);
    
    if (isSweeping_) {
        sweepTimer_ += dt;
        
        if (sweepTimer_ >= sweepDelay_) {
            if (sweepIndex_ < array_.getSize()) {
                array_.setState(sweepIndex_, Array::State::SORTED);
                
                float normalizedValue = array_.getValue(sweepIndex_) / static_cast<float>(array_.getSize());
                float pitch = 0.5f + normalizedValue * 1.5f;
                playBeep(pitch);
                
                sweepIndex_++;
                sweepTimer_ = 0.0f;
            } else {
                isSweeping_ = false;
            }
        }
        return;
    }
    
    if (isPlaying_ && !currentSorter_->isFinished()) {
        size_t beforeComparisons = array_.getComparisons();
        size_t beforeSwaps = array_.getSwaps();
        
        for (int step = 0; step < stepsPerFrame_; ++step) {
            if (currentSorter_->isFinished()) {
                break;
            }
            
            currentSorter_->step(array_);
            opsHistory_.record(array_.getComparisons());
        }
        
        size_t afterComparisons = array_.getComparisons();
        size_t afterSwaps = array_.getSwaps();
        
        if (afterComparisons > beforeComparisons || afterSwaps > beforeSwaps) {
            float avgPitch = 1.0f;
            
            for (int i = 0; i < array_.getSize(); ++i) {
                if (array_.getState(i) == Array::State::COMPARE || 
                    array_.getState(i) == Array::State::SWAP) {
                    float normalizedValue = array_.getValue(i) / static_cast<float>(array_.getSize());
                    avgPitch = 0.5f + normalizedValue * 1.5f;
                    break;
                }
            }
            
            playBeep(avgPitch);
        }
        
        if (currentSorter_->isFinished()) {
            array_.resetStates();
            isSweeping_ = true;
            sweepIndex_ = 0;
            sweepTimer_ = 0.0f;
        }
    }
}

void App::render() {
    window_.clear(sf::Color(10, 12, 20)); 

    const float histogramHeight = 120.0f;
    const float availableHeight = window_.getSize().y - histogramHeight;
    
    float width = window_.getSize().x / static_cast<float>(array_.getSize());
    float maxVal = static_cast<float>(array_.getSize());

    sf::VertexArray vertices(sf::Quads);

    for (int i = 0; i < array_.getSize(); ++i) {
        float height = (array_.getValue(i) / maxVal) * (availableHeight * 0.75f);
        float x = i * width;
        float y = availableHeight - height;
        
        sf::Color barColor;
        bool useGradient = false;
        
        switch (array_.getState(i)) {
            case Array::State::NORMAL:
                useGradient = true;
                break;
            case Array::State::COMPARE:
                barColor = sf::Color(0, 220, 255);
                break;
            case Array::State::SWAP:
                barColor = sf::Color(255, 120, 30);
                break;
            case Array::State::SORTED:
                barColor = sf::Color(50, 220, 120);
                break;
        }
        
        if (useGradient) {
            float normalizedValue = array_.getValue(i) / maxVal;
            sf::Color bottomColor(60, 80, 140);
            sf::Color topColor(160, 180, 255);
            
            sf::Color gradientTop(
                static_cast<sf::Uint8>(bottomColor.r + (topColor.r - bottomColor.r) * normalizedValue),
                static_cast<sf::Uint8>(bottomColor.g + (topColor.g - bottomColor.g) * normalizedValue),
                static_cast<sf::Uint8>(bottomColor.b + (topColor.b - bottomColor.b) * normalizedValue)
            );
            
            sf::Color gradientBottom(
                static_cast<sf::Uint8>(bottomColor.r + (topColor.r - bottomColor.r) * normalizedValue * 0.6f),
                static_cast<sf::Uint8>(bottomColor.g + (topColor.g - bottomColor.g) * normalizedValue * 0.6f),
                static_cast<sf::Uint8>(bottomColor.b + (topColor.b - bottomColor.b) * normalizedValue * 0.6f)
            );
            
            vertices.append(sf::Vertex(sf::Vector2f(x, availableHeight), gradientBottom));
            vertices.append(sf::Vertex(sf::Vector2f(x + width - 1.0f, availableHeight), gradientBottom));
            vertices.append(sf::Vertex(sf::Vector2f(x + width - 1.0f, y), gradientTop));
            vertices.append(sf::Vertex(sf::Vector2f(x, y), gradientTop));
        } else {
            vertices.append(sf::Vertex(sf::Vector2f(x, availableHeight), barColor));
            vertices.append(sf::Vertex(sf::Vector2f(x + width - 1.0f, availableHeight), barColor));
            vertices.append(sf::Vertex(sf::Vector2f(x + width - 1.0f, y), barColor));
            vertices.append(sf::Vertex(sf::Vector2f(x, y), barColor));
        }
    }

    window_.draw(vertices);
    renderHistogram();
    ui_.draw(window_);
    
    window_.display();
}

void App::renderHistogram() {
    const float histogramHeight = 120.0f;
    const float histogramY = window_.getSize().y - histogramHeight;
    
    sf::RectangleShape background(sf::Vector2f(window_.getSize().x, histogramHeight));
    background.setPosition(0.0f, histogramY);
    background.setFillColor(sf::Color(15, 18, 30));
    window_.draw(background);
    
    const auto& history = opsHistory_.getHistory();
    
    if (!history.empty()) {
        size_t maxValue = opsHistory_.getMaxValue();
        if (maxValue == 0) maxValue = 1;
        
        float barWidth = window_.getSize().x / 300.0f;
        sf::VertexArray histogramBars(sf::Quads);
        
        for (size_t i = 0; i < history.size(); ++i) {
            float barHeight = (static_cast<float>(history[i]) / static_cast<float>(maxValue)) * (histogramHeight - 30.0f);
            float x = i * barWidth;
            float y = histogramY + histogramHeight - barHeight - 5.0f;
            
            float normalizedValue = static_cast<float>(history[i]) / static_cast<float>(maxValue);
            sf::Color lowColor(0, 120, 255);
            sf::Color highColor(0, 220, 255);
            
            sf::Color barColor(
                static_cast<sf::Uint8>(lowColor.r + (highColor.r - lowColor.r) * normalizedValue),
                static_cast<sf::Uint8>(lowColor.g + (highColor.g - lowColor.g) * normalizedValue),
                static_cast<sf::Uint8>(lowColor.b + (highColor.b - lowColor.b) * normalizedValue)
            );
            
            histogramBars.append(sf::Vertex(sf::Vector2f(x, histogramY + histogramHeight - 5.0f), barColor));
            histogramBars.append(sf::Vertex(sf::Vector2f(x + barWidth, histogramY + histogramHeight - 5.0f), barColor));
            histogramBars.append(sf::Vertex(sf::Vector2f(x + barWidth, y), barColor));
            histogramBars.append(sf::Vertex(sf::Vector2f(x, y), barColor));
        }
        
        window_.draw(histogramBars);
    }
    
    if (histogramFontLoaded_) {
        sf::Text label;
        label.setFont(histogramFont_);
        label.setString("Comparisons over time");
        label.setCharacterSize(14);
        label.setFillColor(sf::Color(180, 180, 180));
        label.setPosition(10.0f, histogramY + 5.0f);
        window_.draw(label);
    }
}

void App::switchSorter(std::unique_ptr<Sorter> newSorter) {
    currentSorter_ = std::move(newSorter);
    array_.shuffle();
    array_.resetStates();
    array_.resetCounters();
    opsHistory_.reset();
    isPlaying_ = false;
    timeSinceLastStep_ = 0.0f;
    isSweeping_ = false;
    sweepIndex_ = 0;
    lastComparisons_ = 0;
    lastSwaps_ = 0;
    stepsPerFrame_ = 1;
}
