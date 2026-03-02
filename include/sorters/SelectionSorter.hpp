#pragma once
#include "Sorter.hpp"

class SelectionSorter : public Sorter {
public:
    SelectionSorter();
    
    void step(Array& array) override;
    bool isFinished() const override;
    std::string getName() const override;
    void reset() override;

private:
    enum class Phase { FINDING_MIN, SWAPPING, NEXT };
    
    int i_;
    int j_;
    int minIndex_;
    int n_;
    bool finished_;
    Phase phase_;
};
