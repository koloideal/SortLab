#include "App.hpp"
#include "sorters/BubbleSorter.hpp"
#include "sorters/SelectionSorter.hpp"
#include "sorters/InsertionSorter.hpp"
#include "sorters/MergeSorter.hpp"
#include "sorters/QuickSorter.hpp"

App::App() 
    : window_(sf::VideoMode(1280, 720), "SortLab")
    , array_(100)
    , currentSorter_(std::make_unique<BubbleSorter>())
    , ui_()
    , isPlaying_(false)
    , timeSinceLastStep_(0.0f)
    , stepsPerFrame_(1)
    , isSweeping_(false)
    , sweepIndex_(0)
    , sweepTimer_(0.0f)
    , sweepDelay_(0.005f)
    , lastComparisons_(0)
    , lastSwaps_(0) {
    window_.setFramerateLimit(60);
    generateBeepSound();
    beepSound_.setBuffer(beepBuffer_);
    beepSound_.setVolume(100.0f);
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
                    isPlaying_ = false;
                    timeSinceLastStep_ = 0.0f;
                    isSweeping_ = false;
                    sweepIndex_ = 0;
                    lastComparisons_ = 0;
                    lastSwaps_ = 0;
                    stepsPerFrame_ = 1;
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
    window_.clear(sf::Color(18, 18, 22)); 

    float width = window_.getSize().x / static_cast<float>(array_.getSize());
    float maxVal = static_cast<float>(array_.getSize());

    for (int i = 0; i < array_.getSize(); ++i) {
        float height = (array_.getValue(i) / maxVal) * (window_.getSize().y * 0.8f);
        
        sf::RectangleShape bar(sf::Vector2f(width - 1.0f, height)); 
        bar.setPosition(i * width, window_.getSize().y - height);   

        switch (array_.getState(i)) {
            case Array::State::NORMAL:  bar.setFillColor(sf::Color(200, 200, 200)); break;
            case Array::State::COMPARE: bar.setFillColor(sf::Color::Yellow); break;
            case Array::State::SWAP:    bar.setFillColor(sf::Color::Red); break;
            case Array::State::SORTED:  bar.setFillColor(sf::Color::Green); break;
        }

        window_.draw(bar);
    }

    ui_.draw(window_);
    
    window_.display();
}

void App::switchSorter(std::unique_ptr<Sorter> newSorter) {
    currentSorter_ = std::move(newSorter);
    array_.shuffle();
    array_.resetStates();
    array_.resetCounters();
    isPlaying_ = false;
    timeSinceLastStep_ = 0.0f;
    isSweeping_ = false;
    sweepIndex_ = 0;
    lastComparisons_ = 0;
    lastSwaps_ = 0;
    stepsPerFrame_ = 1;
}
