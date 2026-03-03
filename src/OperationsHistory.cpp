#include "OperationsHistory.hpp"
#include <algorithm>

OperationsHistory::OperationsHistory(size_t maxSamples) 
    : maxSamples_(maxSamples) {
}

void OperationsHistory::record(size_t comparisons) {
    compareHistory_.push_back(comparisons);
    
    if (compareHistory_.size() > maxSamples_) {
        compareHistory_.pop_front();
    }
}

void OperationsHistory::reset() {
    compareHistory_.clear();
}

const std::deque<size_t>& OperationsHistory::getHistory() const {
    return compareHistory_;
}

size_t OperationsHistory::getMaxValue() const {
    if (compareHistory_.empty()) {
        return 1;
    }
    
    return *std::max_element(compareHistory_.begin(), compareHistory_.end());
}
