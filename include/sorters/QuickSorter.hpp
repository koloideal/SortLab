#pragma once
#include "Sorter.hpp"
#include <vector>

class QuickSorter : public Sorter {
public:
    QuickSorter();
    void step(Array& array) override;
    bool isFinished() const override;
    std::string getName() const override;
    std::string getTimeComplexity() const override;
    std::string getSpaceComplexity() const override;
    void reset() override;

private:
    struct Range { int low; int high; };
    enum class Phase { PARTITIONING, SWAPPING_PIVOT, PUSHING_RANGES };

    std::vector<Range> stack_;
    Phase phase_;
    int currentLow_, currentHigh_, pivotIndex_, i_, j_, n_;
    float pivotValue_;
    bool finished_;
    bool needNewRange_;  
};
