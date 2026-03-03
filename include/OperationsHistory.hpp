#pragma once
#include <deque>
#include <cstddef>

class OperationsHistory {
public:
    OperationsHistory(size_t maxSamples = 400);
    
    void record(size_t currentComparisons);
    void reset();
    const std::deque<size_t>& getDeltaHistory() const;
    size_t getMaxDelta() const;

private:
    std::deque<size_t> deltaHistory_;
    size_t maxSamples_;
    size_t lastComparisons_;
};
