#include "App.hpp"
#include <cmath>
#include <vector>

void App::generateBeepSound() {
    const unsigned int sampleRate = 44100;
    const float duration = 0.02f;
    const unsigned int sampleCount = static_cast<unsigned int>(sampleRate * duration);
    
    std::vector<sf::Int16> samples(sampleCount);
    
    const float frequency = 440.0f;
    const float amplitude = 3000.0f;
    
    for (unsigned int i = 0; i < sampleCount; ++i) {
        float t = static_cast<float>(i) / sampleRate;
        float envelope = 1.0f - (t / duration);
        float value = amplitude * envelope * std::sin(2.0f * 3.14159f * frequency * t);
        samples[i] = static_cast<sf::Int16>(value);
    }
    
    beepBuffer_.loadFromSamples(samples.data(), sampleCount, 1, sampleRate);
}

void App::playBeep(float pitch) {
    if (beepSound_.getStatus() != sf::Sound::Playing) {
        beepSound_.setPitch(pitch);
        beepSound_.play();
    }
}
