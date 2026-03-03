#include "OperationsHistory.hpp"
#include <algorithm>

OperationsHistory::OperationsHistory(size_t maxSamples) 
    : maxSamples_(maxSamples), lastComparisons_(0) {
}

void OperationsHistory::record(size_t currentComparisons) {
    size_t delta = 0;
    if (currentComparisons >= lastComparisons_) {
        delta = currentComparisons - lastComparisons_;
    }
    
    deltaHistory_.push_back(delta);
    lastComparisons_ = currentComparisons;
    
    if (deltaHistory_.size() > maxSamples_) {
        deltaHistory_.pop_front();
    }
}

void OperationsHistory::reset() {
    deltaHistory_.clear();
    lastComparisons_ = 0;
}

const std::deque<size_t>& OperationsHistory::getDeltaHistory() const {
    return deltaHistory_;
}

size_t OperationsHistory::getMaxDelta() const {
    if (deltaHistory_.empty()) {
        return 1;
    }
    
    return *std::max_element(deltaHistory_.begin(), deltaHistory_.end());
}
