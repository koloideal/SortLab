#pragma once
#include "Sorter.hpp"
#include <vector>

class QuickSorter : public Sorter {
public:
    QuickSorter();
    
    void step(Array& array) override;
    bool isFinished() const override;
    std::string getName() const override;
    void reset() override;
    std::string getTimeComplexity() const override;
    std::string getSpaceComplexity() const override;

private:
    enum class Phase { PARTITIONING, SWAPPING_PIVOT, PUSHING_RANGES };
    
    struct Range {
        int low;
        int high;
    };
    
    std::vector<Range> stack_;
    int currentLow_;
    int currentHigh_;
    int pivotIndex_;
    int i_;
    int j_;
    float pivotValue_;
    bool finished_;
    Phase phase_;
    int n_;
};
