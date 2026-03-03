#pragma once
#include <deque>
#include <cstddef>

class OperationsHistory {
public:
    OperationsHistory(size_t maxSamples = 300);
    
    void record(size_t comparisons);
    void reset();
    const std::deque<size_t>& getHistory() const;
    size_t getMaxValue() const;

private:
    std::deque<size_t> compareHistory_;
    size_t maxSamples_;
};
