#pragma once
#include <vector>

class Array {
public:
    enum class State { NORMAL, COMPARE, SWAP, SORTED };

    Array(int size);
    void shuffle();
    
    int getSize() const;
    float getValue(int index) const;
    State getState(int index) const;
    
    void setValue(int index, float value);
    void setState(int index, State state);
    void resetStates();
    void resetCounters();
    
    size_t getComparisons() const;
    size_t getSwaps() const;
    void incrementComparisons();
    void incrementSwaps();

private:
    std::vector<float> data_;
    std::vector<State> states_;
    size_t comparisons_;
    size_t swaps_;
};
