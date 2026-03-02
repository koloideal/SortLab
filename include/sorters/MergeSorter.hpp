#pragma once
#include "Sorter.hpp"
#include <vector>

class MergeSorter : public Sorter {
public:
    MergeSorter();
    
    void step(Array& array) override;
    bool isFinished() const override;
    std::string getName() const override;
    void reset() override;

private:
    enum class Phase { MERGING, COPYING_LEFT, COPYING_RIGHT, COPYING_BACK, NEXT_MERGE };
    
    int currentSize_;
    int leftStart_;
    int mid_;
    int rightEnd_;
    int leftIndex_;
    int rightIndex_;
    int mergeIndex_;
    std::vector<float> temp_;
    bool finished_;
    Phase phase_;
    int n_;
};
