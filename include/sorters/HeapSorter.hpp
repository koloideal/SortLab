#pragma once
#include "Sorter.hpp"

class HeapSorter : public Sorter {
public:
    HeapSorter();
    
    void step(Array& array) override;
    bool isFinished() const override;
    std::string getName() const override;
    void reset() override;
    std::string getTimeComplexity() const override;
    std::string getSpaceComplexity() const override;

private:
    enum class Phase { BUILDING_HEAP, HEAPIFY_DOWN, EXTRACTING, EXTRACT_SWAP, EXTRACT_HEAPIFY };
    
    int n_;
    int heapSize_;
    int buildIndex_;
    int extractIndex_;
    int heapifyIndex_;
    int leftChild_;
    int rightChild_;
    int largest_;
    bool finished_;
    Phase phase_;
    bool needSwap_;
};
