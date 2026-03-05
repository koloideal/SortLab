#pragma once
#include "Sorter.hpp"

class ShellSorter : public Sorter {
public:
    ShellSorter();
    
    void step(Array& array) override;
    bool isFinished() const override;
    std::string getName() const override;
    void reset() override;
    std::string getTimeComplexity() const override;
    std::string getSpaceComplexity() const override;

private:
    enum class Phase { COMPARING, SHIFTING, PLACING };
    
    int n_;
    int gap_;
    int i_;
    int j_;
    float temp_;
    bool finished_;
    Phase phase_;
};
