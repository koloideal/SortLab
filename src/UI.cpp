#pragma execution_character_set("utf-8")
#include "UI.hpp"
#include <iostream>

UI::UI() : fontLoaded_(false) {
    if (!font_.loadFromFile("assets/fonts/JetBrainsMono-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }
    
    fontLoaded_ = true;
    
    algorithmText_.setFont(font_);
    algorithmText_.setCharacterSize(28);
    algorithmText_.setFillColor(sf::Color::White);
    algorithmText_.setPosition(15.0f, 15.0f);
    
    stateText_.setFont(font_);
    stateText_.setCharacterSize(20);
    stateText_.setFillColor(sf::Color::White);
    stateText_.setPosition(15.0f, 50.0f);
    
    timeComplexityText_.setFont(font_);
    timeComplexityText_.setCharacterSize(16);
    timeComplexityText_.setFillColor(sf::Color(160, 160, 160));
    timeComplexityText_.setPosition(15.0f, 80.0f);
    
    spaceComplexityText_.setFont(font_);
    spaceComplexityText_.setCharacterSize(16);
    spaceComplexityText_.setFillColor(sf::Color(160, 160, 160));
    spaceComplexityText_.setPosition(15.0f, 105.0f);
    
    comparisonsText_.setFont(font_);
    comparisonsText_.setCharacterSize(18);
    comparisonsText_.setFillColor(sf::Color(220, 220, 220));
    comparisonsText_.setPosition(15.0f, 135.0f);
    
    swapsText_.setFont(font_);
    swapsText_.setCharacterSize(18);
    swapsText_.setFillColor(sf::Color(220, 220, 220));
    swapsText_.setPosition(15.0f, 160.0f);
    
    speedText_.setFont(font_);
    speedText_.setCharacterSize(18);
    speedText_.setFillColor(sf::Color(220, 220, 220));
    speedText_.setPosition(15.0f, 185.0f);
    
    controlsText_.setFont(font_);
    controlsText_.setCharacterSize(15);
    controlsText_.setFillColor(sf::Color(200, 200, 200));
    controlsText_.setString("[1-5] Algorithms  [Space] Play/Pause  [Right] Step  [Up/Down] Speed  [R] Shuffle");
    
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
    
    sf::FloatRect algoBounds = algorithmText_.getLocalBounds();
    sf::FloatRect stateBounds = stateText_.getLocalBounds();
    sf::FloatRect timeBounds = timeComplexityText_.getLocalBounds();
    sf::FloatRect spaceBounds = spaceComplexityText_.getLocalBounds();
    sf::FloatRect compBounds = comparisonsText_.getLocalBounds();
    sf::FloatRect swapBounds = swapsText_.getLocalBounds();
    sf::FloatRect speedBounds = speedText_.getLocalBounds();
    
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
    
    sf::FloatRect controlsBounds = controlsText_.getLocalBounds();
    float rightWidth = controlsBounds.width + 20.0f;
    float rightHeight = controlsBounds.height + 20.0f;
    float windowWidth = static_cast<float>(window.getSize().x);
    
    rightBackground_.setSize(sf::Vector2f(rightWidth, rightHeight));
    rightBackground_.setPosition(windowWidth - rightWidth - 5.0f, 5.0f);
    
    controlsText_.setPosition(windowWidth - controlsBounds.width - 15.0f, 15.0f);
    
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
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::White);
    title.setString(toSfStr(u8"SortLab — визуализатор алгоритмов сортировки"));
    
    sf::Text subtitle;
    subtitle.setFont(font_);
    subtitle.setCharacterSize(18);
    subtitle.setFillColor(sf::Color(160, 160, 160));
    subtitle.setString(toSfStr(u8"Учебный инструмент для наглядного изучения алгоритмов сортировки"));
    
    sf::Text section1;
    section1.setFont(font_);
    section1.setCharacterSize(20);
    section1.setFillColor(sf::Color(0, 220, 255));
    section1.setString(toSfStr(u8"О программе"));
    
    sf::Text body1;
    body1.setFont(font_);
    body1.setCharacterSize(16);
    body1.setFillColor(sf::Color(200, 200, 200));
    body1.setString(toSfStr(u8"SortLab визуализирует работу алгоритмов сортировки в реальном времени.\nКаждый столбик — это элемент массива. Высота = значение элемента.\nЦвета: серый — обычный, голубой — сравнение, оранжевый — перестановка, зелёный — готово."));
    
    sf::Text section2;
    section2.setFont(font_);
    section2.setCharacterSize(20);
    section2.setFillColor(sf::Color(0, 220, 255));
    section2.setString(toSfStr(u8"Алгоритмы и сложность"));
    
    sf::Text body2;
    body2.setFont(font_);
    body2.setCharacterSize(16);
    body2.setFillColor(sf::Color(200, 200, 200));
    body2.setString(toSfStr(u8"[1] Bubble Sort      Время: O(n²) / O(n²) / O(n²)         Память: O(1)\n[2] Selection Sort   Время: O(n²) / O(n²) / O(n²)         Память: O(1)\n[3] Insertion Sort   Время: O(n) / O(n²) / O(n²)          Память: O(1)\n[4] Merge Sort       Время: O(n log n) / O(n log n) / ...  Память: O(n)\n[5] Quick Sort       Время: O(n log n) / O(n log n) / ...  Память: O(log n)"));
    
    sf::Text section3;
    section3.setFont(font_);
    section3.setCharacterSize(20);
    section3.setFillColor(sf::Color(0, 220, 255));
    section3.setString(toSfStr(u8"Δ Гистограмма (внизу слева)"));
    
    sf::Text body3;
    body3.setFont(font_);
    body3.setCharacterSize(16);
    body3.setFillColor(sf::Color(200, 200, 200));
    body3.setString(toSfStr(u8"Показывает количество сравнений на каждом шаге сортировки.\nВысокий пик = много сравнений за один шаг.\nBubble Sort даёт ровную линию, Quick Sort — резкие пики в начале."));
    
    sf::Text section4;
    section4.setFont(font_);
    section4.setCharacterSize(20);
    section4.setFillColor(sf::Color(0, 220, 255));
    section4.setString(toSfStr(u8"Карта прогресса (внизу справа)"));
    
    sf::Text body4;
    body4.setFont(font_);
    body4.setCharacterSize(16);
    body4.setFillColor(sf::Color(200, 200, 200));
    body4.setString(toSfStr(u8"Миниатюрная копия всего массива в виде сетки цветных квадратиков.\nПозволяет видеть глобальный прогресс сортировки даже при большом массиве.\nЗелёные квадраты = отсортированные элементы."));
    
    sf::Text footer;
    footer.setFont(font_);
    footer.setCharacterSize(15);
    footer.setFillColor(sf::Color(100, 100, 100));
    footer.setString(toSfStr(u8"Нажми [I] чтобы закрыть  |  [Q] выход  |  [Space] старт/пауза  |  [R] перемешать"));
    
    float totalHeight = 0.0f;
    totalHeight += title.getLocalBounds().height + 10.0f;
    totalHeight += subtitle.getLocalBounds().height + 30.0f;
    totalHeight += section1.getLocalBounds().height + 6.0f;
    totalHeight += body1.getLocalBounds().height + 24.0f;
    totalHeight += section2.getLocalBounds().height + 6.0f;
    totalHeight += body2.getLocalBounds().height + 24.0f;
    totalHeight += section3.getLocalBounds().height + 6.0f;
    totalHeight += body3.getLocalBounds().height + 24.0f;
    totalHeight += section4.getLocalBounds().height + 6.0f;
    totalHeight += body4.getLocalBounds().height + 30.0f;
    totalHeight += footer.getLocalBounds().height;
    
    float startY = (windowHeight - totalHeight) * 0.5f;
    if (startY < 20.0f) startY = 20.0f;
    
    float currentY = startY;
    
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition((windowWidth - titleBounds.width) * 0.5f, currentY);
    window.draw(title);
    currentY += titleBounds.height + 10.0f;
    
    sf::FloatRect subtitleBounds = subtitle.getLocalBounds();
    subtitle.setPosition((windowWidth - subtitleBounds.width) * 0.5f, currentY);
    window.draw(subtitle);
    currentY += subtitleBounds.height + 30.0f;
    
    sf::FloatRect section1Bounds = section1.getLocalBounds();
    section1.setPosition((windowWidth - section1Bounds.width) * 0.5f, currentY);
    window.draw(section1);
    currentY += section1Bounds.height + 6.0f;
    
    sf::FloatRect body1Bounds = body1.getLocalBounds();
    body1.setPosition((windowWidth - body1Bounds.width) * 0.5f, currentY);
    window.draw(body1);
    currentY += body1Bounds.height + 24.0f;
    
    sf::FloatRect section2Bounds = section2.getLocalBounds();
    section2.setPosition((windowWidth - section2Bounds.width) * 0.5f, currentY);
    window.draw(section2);
    currentY += section2Bounds.height + 6.0f;
    
    sf::FloatRect body2Bounds = body2.getLocalBounds();
    body2.setPosition((windowWidth - body2Bounds.width) * 0.5f, currentY);
    window.draw(body2);
    currentY += body2Bounds.height + 24.0f;
    
    sf::FloatRect section3Bounds = section3.getLocalBounds();
    section3.setPosition((windowWidth - section3Bounds.width) * 0.5f, currentY);
    window.draw(section3);
    currentY += section3Bounds.height + 6.0f;
    
    sf::FloatRect body3Bounds = body3.getLocalBounds();
    body3.setPosition((windowWidth - body3Bounds.width) * 0.5f, currentY);
    window.draw(body3);
    currentY += body3Bounds.height + 24.0f;
    
    sf::FloatRect section4Bounds = section4.getLocalBounds();
    section4.setPosition((windowWidth - section4Bounds.width) * 0.5f, currentY);
    window.draw(section4);
    currentY += section4Bounds.height + 6.0f;
    
    sf::FloatRect body4Bounds = body4.getLocalBounds();
    body4.setPosition((windowWidth - body4Bounds.width) * 0.5f, currentY);
    window.draw(body4);
    currentY += body4Bounds.height + 30.0f;
    
    sf::FloatRect footerBounds = footer.getLocalBounds();
    footer.setPosition((windowWidth - footerBounds.width) * 0.5f, currentY);
    window.draw(footer);
}
