#pragma once
#include "Sorter.hpp"
#include <vector>

class RadixSorter : public Sorter {
public:
    RadixSorter();
    
    void step(Array& array) override;
    bool isFinished() const override;
    std::string getName() const override;
    void reset() override;
    std::string getTimeComplexity() const override;
    std::string getSpaceComplexity() const override;

private:
    enum class Phase { INIT, COUNTING, PLACING, COPYING_BACK };
    
    int n_;
    int maxValue_;
    int exp_;
    int i_;
    std::vector<int> count_;
    std::vector<float> output_;
    bool finished_;
    Phase phase_;
};
