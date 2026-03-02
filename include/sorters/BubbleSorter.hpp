#pragma once
#include "Sorter.hpp"

class BubbleSorter : public Sorter {
public:
    BubbleSorter();
    
    void step(Array& array) override;
    bool isFinished() const override;
    std::string getName() const override;
    void reset() override;

private:
    enum class Phase { COMPARING, SWAPPING, NEXT };
    
    int i_;
    int j_;
    int n_;
    bool finished_;
    Phase phase_;
};
