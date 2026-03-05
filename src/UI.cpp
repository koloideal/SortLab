#pragma execution_character_set("utf-8")
#include "UI.hpp"
#include <iostream>
#include <cmath>

UI::UI() : fontLoaded_(false) {
    if (!font_.loadFromFile("assets/fonts/JetBrainsMono-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    
    font_.setSmooth(true);
    fontLoaded_ = true;
    
    algorithmText_.setFont(font_);
    algorithmText_.setCharacterSize(56);
    algorithmText_.setScale(0.5f, 0.5f);
    algorithmText_.setFillColor(sf::Color::White);
    algorithmText_.setPosition(15.0f, 15.0f);
    
    stateText_.setFont(font_);
    stateText_.setCharacterSize(40);
    stateText_.setScale(0.5f, 0.5f);
    stateText_.setFillColor(sf::Color::White);
    stateText_.setPosition(15.0f, 50.0f);
    
    timeComplexityText_.setFont(font_);
    timeComplexityText_.setCharacterSize(32);
    timeComplexityText_.setScale(0.5f, 0.5f);
    timeComplexityText_.setFillColor(sf::Color(160, 160, 160));
    timeComplexityText_.setPosition(15.0f, 80.0f);
    
    spaceComplexityText_.setFont(font_);
    spaceComplexityText_.setCharacterSize(32);
    spaceComplexityText_.setScale(0.5f, 0.5f);
    spaceComplexityText_.setFillColor(sf::Color(160, 160, 160));
    spaceComplexityText_.setPosition(15.0f, 105.0f);
    
    comparisonsText_.setFont(font_);
    comparisonsText_.setCharacterSize(36);
    comparisonsText_.setScale(0.5f, 0.5f);
    comparisonsText_.setFillColor(sf::Color(220, 220, 220));
    comparisonsText_.setPosition(15.0f, 135.0f);
    
    swapsText_.setFont(font_);
    swapsText_.setCharacterSize(36);
    swapsText_.setScale(0.5f, 0.5f);
    swapsText_.setFillColor(sf::Color(220, 220, 220));
    swapsText_.setPosition(15.0f, 160.0f);
    
    speedText_.setFont(font_);
    speedText_.setCharacterSize(36);
    speedText_.setScale(0.5f, 0.5f);
    speedText_.setFillColor(sf::Color(220, 220, 220));
    speedText_.setPosition(15.0f, 185.0f);
    
    controlsText_.setFont(font_);
    controlsText_.setCharacterSize(30);
    controlsText_.setScale(0.5f, 0.5f);
    controlsText_.setFillColor(sf::Color(200, 200, 200));
    controlsText_.setString("[1-8] Algorithms  [Space] Play/Pause  [Right] Step  [Up/Down] Speed  [R] Shuffle");
    
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
    
    float maxWidth = 0.0f;
    
    sf::FloatRect algoBounds = algorithmText_.getGlobalBounds();
    sf::FloatRect stateBounds = stateText_.getGlobalBounds();
    sf::FloatRect timeBounds = timeComplexityText_.getGlobalBounds();
    sf::FloatRect spaceBounds = spaceComplexityText_.getGlobalBounds();
    sf::FloatRect compBounds = comparisonsText_.getGlobalBounds();
    sf::FloatRect swapBounds = swapsText_.getGlobalBounds();
    sf::FloatRect speedBounds = speedText_.getGlobalBounds();
    
    maxWidth = std::max(maxWidth, algoBounds.width);
    maxWidth = std::max(maxWidth, stateBounds.width);
    maxWidth = std::max(maxWidth, timeBounds.width);
    maxWidth = std::max(maxWidth, spaceBounds.width);
    maxWidth = std::max(maxWidth, compBounds.width);
    maxWidth = std::max(maxWidth, swapBounds.width);
    maxWidth = std::max(maxWidth, speedBounds.width);
    
    float leftWidth = maxWidth + 24.0f;
    float leftHeight = 215.0f;
    leftBackground_.setSize(sf::Vector2f(leftWidth, leftHeight));
    leftBackground_.setPosition(5.0f, 5.0f);
    
    sf::FloatRect controlsBounds = controlsText_.getGlobalBounds();
    float rightWidth = controlsBounds.width + 20.0f;
    float rightHeight = controlsBounds.height + 20.0f;
    float windowWidth = static_cast<float>(window.getSize().x);
    
    rightBackground_.setSize(sf::Vector2f(rightWidth, rightHeight));
    rightBackground_.setPosition(windowWidth - rightWidth - 5.0f, 5.0f);
    
    controlsText_.setPosition(std::floor(windowWidth - controlsBounds.width - 15.0f), std::floor(15.0f));
    
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

void UI::drawInfoOverlay(sf::RenderWindow& window) {
    if (!fontLoaded_) {
        return;
    }
    
    auto toSfStr = [](const char* utf8) -> sf::String {
        std::string s(utf8);
        return sf::String::fromUtf8(s.begin(), s.end());
    };
    
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);
    
    sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
    overlay.setPosition(0.0f, 0.0f);
    overlay.setFillColor(sf::Color(8, 10, 18, 230));
    window.draw(overlay);
    
    sf::Text title;
    title.setFont(font_);
    title.setCharacterSize(80);
    title.setScale(0.5f, 0.5f);
    title.setFillColor(sf::Color::White);
    title.setString(toSfStr(u8"SortLab — визуализатор алгоритмов сортировки"));
    
    sf::Text subtitle;
    subtitle.setFont(font_);
    subtitle.setCharacterSize(38);
    subtitle.setScale(0.5f, 0.5f);
    subtitle.setFillColor(sf::Color(160, 160, 160));
    subtitle.setString(toSfStr(u8"Учебный инструмент для наглядного изучения алгоритмов сортировки"));
    
    sf::Text section1;
    section1.setFont(font_);
    section1.setCharacterSize(42);
    section1.setScale(0.5f, 0.5f);
    section1.setFillColor(sf::Color(0, 220, 255));
    section1.setString(toSfStr(u8"О программе"));
    
    sf::Text body1;
    body1.setFont(font_);
    body1.setCharacterSize(32);
    body1.setScale(0.5f, 0.5f);
    body1.setFillColor(sf::Color(200, 200, 200));
    body1.setString(toSfStr(u8"SortLab визуализирует работу алгоритмов сортировки в реальном времени.\nКаждый столбик — это элемент массива. Высота = значение элемента.\nЦвета: серый — обычный, голубой — сравнение, оранжевый — перестановка, зелёный — готово."));
    
    sf::Text section2;
    section2.setFont(font_);
    section2.setCharacterSize(42);
    section2.setScale(0.5f, 0.5f);
    section2.setFillColor(sf::Color(0, 220, 255));
    section2.setString(toSfStr(u8"Алгоритмы и сложность"));
    
    sf::Text body2;
    body2.setFont(font_);
    body2.setCharacterSize(32);
    body2.setScale(0.5f, 0.5f);
    body2.setFillColor(sf::Color(200, 200, 200));
    body2.setString(toSfStr(u8"[1] Bubble Sort      Время: O(n) / O(n^2) / O(n^2)              Память: O(1)\n[2] Selection Sort   Время: O(n^2) / O(n^2) / O(n^2)           Память: O(1)\n[3] Insertion Sort   Время: O(n) / O(n^2) / O(n^2)             Память: O(1)\n[4] Merge Sort       Время: O(n log n) / O(n log n) / O(n log n)  Память: O(n)\n[5] Quick Sort       Время: O(n log n) / O(n log n) / O(n^2)   Память: O(log n)\n[6] Heap Sort        Время: O(n log n)                         Память: O(1)\n[7] Shell Sort       Время: O(n log^2 n)                       Память: O(1)\n[8] Radix Sort       Время: O(n*k)                             Память: O(n + k)"));
    
    sf::Text section3;
    section3.setFont(font_);
    section3.setCharacterSize(42);
    section3.setScale(0.5f, 0.5f);
    section3.setFillColor(sf::Color(0, 220, 255));
    section3.setString(toSfStr(u8"Гистограмма (внизу слева)"));
    
    sf::Text body3;
    body3.setFont(font_);
    body3.setCharacterSize(32);
    body3.setScale(0.5f, 0.5f);
    body3.setFillColor(sf::Color(200, 200, 200));
    body3.setString(toSfStr(u8"Показывает количество сравнений на каждом шаге сортировки.\nВысокий пик = много сравнений за один шаг.\nBubble Sort даёт ровную линию, Quick Sort — резкие пики в начале."));
    
    sf::Text section4;
    section4.setFont(font_);
    section4.setCharacterSize(42);
    section4.setScale(0.5f, 0.5f);
    section4.setFillColor(sf::Color(0, 220, 255));
    section4.setString(toSfStr(u8"Карта прогресса (внизу справа)"));
    
    sf::Text body4;
    body4.setFont(font_);
    body4.setCharacterSize(32);
    body4.setScale(0.5f, 0.5f);
    body4.setFillColor(sf::Color(200, 200, 200));
    body4.setString(toSfStr(u8"Миниатюрная копия всего массива в виде сетки цветных квадратиков.\nПозволяет видеть глобальный прогресс сортировки даже при большом массиве.\nЗелёные квадраты = отсортированные элементы."));
    
    sf::Text footer;
    footer.setFont(font_);
    footer.setCharacterSize(30);
    footer.setScale(0.5f, 0.5f);
    footer.setFillColor(sf::Color(100, 100, 100));
    footer.setString(toSfStr(u8"Нажми [I] чтобы закрыть  |  [Q] выход  |  [Space] старт/пауза  |  [R] перемешать"));
    
    float totalHeight = 0.0f;
    totalHeight += title.getGlobalBounds().height + 10.0f;
    totalHeight += subtitle.getGlobalBounds().height + 30.0f;
    totalHeight += section1.getGlobalBounds().height + 6.0f;
    totalHeight += body1.getGlobalBounds().height + 24.0f;
    totalHeight += section2.getGlobalBounds().height + 6.0f;
    totalHeight += body2.getGlobalBounds().height + 24.0f;
    totalHeight += section3.getGlobalBounds().height + 6.0f;
    totalHeight += body3.getGlobalBounds().height + 24.0f;
    totalHeight += section4.getGlobalBounds().height + 6.0f;
    totalHeight += body4.getGlobalBounds().height + 30.0f;
    totalHeight += footer.getGlobalBounds().height;
    
    float startY = (windowHeight - totalHeight) * 0.5f;
    if (startY < 20.0f) startY = 20.0f;
    
    float currentY = startY;
    
    sf::FloatRect titleBounds = title.getGlobalBounds();
    title.setPosition(std::floor((windowWidth - titleBounds.width) * 0.5f), std::floor(currentY));
    window.draw(title);
    currentY += titleBounds.height + 10.0f;
    
    sf::FloatRect subtitleBounds = subtitle.getGlobalBounds();
    subtitle.setPosition(std::floor((windowWidth - subtitleBounds.width) * 0.5f), std::floor(currentY));
    window.draw(subtitle);
    currentY += subtitleBounds.height + 30.0f;
    
    sf::FloatRect section1Bounds = section1.getGlobalBounds();
    section1.setPosition(std::floor((windowWidth - section1Bounds.width) * 0.5f), std::floor(currentY));
    window.draw(section1);
    currentY += section1Bounds.height + 6.0f;
    
    sf::FloatRect body1Bounds = body1.getGlobalBounds();
    body1.setPosition(std::floor((windowWidth - body1Bounds.width) * 0.5f), std::floor(currentY));
    window.draw(body1);
    currentY += body1Bounds.height + 24.0f;
    
    sf::FloatRect section2Bounds = section2.getGlobalBounds();
    section2.setPosition(std::floor((windowWidth - section2Bounds.width) * 0.5f), std::floor(currentY));
    window.draw(section2);
    currentY += section2Bounds.height + 6.0f;
    
    sf::FloatRect body2Bounds = body2.getGlobalBounds();
    body2.setPosition(std::floor((windowWidth - body2Bounds.width) * 0.5f), std::floor(currentY));
    window.draw(body2);
    currentY += body2Bounds.height + 24.0f;
    
    sf::FloatRect section3Bounds = section3.getGlobalBounds();
    section3.setPosition(std::floor((windowWidth - section3Bounds.width) * 0.5f), std::floor(currentY));
    window.draw(section3);
    currentY += section3Bounds.height + 6.0f;
    
    sf::FloatRect body3Bounds = body3.getGlobalBounds();
    body3.setPosition(std::floor((windowWidth - body3Bounds.width) * 0.5f), std::floor(currentY));
    window.draw(body3);
    currentY += body3Bounds.height + 24.0f;
    
    sf::FloatRect section4Bounds = section4.getGlobalBounds();
    section4.setPosition(std::floor((windowWidth - section4Bounds.width) * 0.5f), std::floor(currentY));
    window.draw(section4);
    currentY += section4Bounds.height + 6.0f;
    
    sf::FloatRect body4Bounds = body4.getGlobalBounds();
    body4.setPosition(std::floor((windowWidth - body4Bounds.width) * 0.5f), std::floor(currentY));
    window.draw(body4);
    currentY += body4Bounds.height + 30.0f;
    
    sf::FloatRect footerBounds = footer.getGlobalBounds();
    footer.setPosition(std::floor((windowWidth - footerBounds.width) * 0.5f), std::floor(currentY));
    window.draw(footer);
}
