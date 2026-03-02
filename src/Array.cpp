#include "Array.hpp"
#include <random>
#include <algorithm>

Array::Array(int size) : comparisons_(0), swaps_(0) {
    data_.resize(size);
    states_.resize(size, State::NORMAL);
    shuffle();
}

void Array::shuffle() {
    for (int i = 0; i < data_.size(); ++i) {
        data_[i] = static_cast<float>(i + 1);
    }
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data_.begin(), data_.end(), g);
    
    resetStates();
}

int Array::getSize() const { return data_.size(); }
float Array::getValue(int index) const { return data_[index]; }
Array::State Array::getState(int index) const { return states_[index]; }

void Array::setValue(int index, float value) { data_[index] = value; }
void Array::setState(int index, State state) { states_[index] = state; }

void Array::resetStates() {
    std::fill(states_.begin(), states_.end(), State::NORMAL);
}

void Array::resetCounters() {
    comparisons_ = 0;
    swaps_ = 0;
}

size_t Array::getComparisons() const {
    return comparisons_;
}

size_t Array::getSwaps() const {
    return swaps_;
}

void Array::incrementComparisons() {
    comparisons_++;
}

void Array::incrementSwaps() {
    swaps_++;
}
