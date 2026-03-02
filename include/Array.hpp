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

private:
    std::vector<float> data_;
    std::vector<State> states_;
};
