#include "sorters/HeapSorter.hpp"

HeapSorter::HeapSorter() {
    reset();
}

void HeapSorter::step(Array& array) {
    if (finished_) return;
    
    if (n_ == 0) {
        n_ = array.getSize();
        if (n_ <= 1) {
            finished_ = true;
            return;
        }
        heapSize_ = n_;
        buildIndex_ = n_ / 2 - 1;
        phase_ = Phase::BUILDING_HEAP;
        heapifyIndex_ = buildIndex_;
    }
    
    if (phase_ == Phase::BUILDING_HEAP) {
        if (buildIndex_ < 0) {
            phase_ = Phase::EXTRACTING;
            extractIndex_ = n_ - 1;
            return;
        }
        heapifyIndex_ = buildIndex_;
        phase_ = Phase::HEAPIFY_DOWN;
        needSwap_ = false;
    } 
    else if (phase_ == Phase::HEAPIFY_DOWN || phase_ == Phase::EXTRACT_HEAPIFY) {
        leftChild_ = 2 * heapifyIndex_ + 1;
        rightChild_ = 2 * heapifyIndex_ + 2;
        largest_ = heapifyIndex_;
        
        array.resetStates();
        array.setState(heapifyIndex_, Array::State::COMPARE);
        
        if (leftChild_ < heapSize_) {
            array.setState(leftChild_, Array::State::COMPARE);
            array.incrementComparisons();
            if (array.getValue(leftChild_) > array.getValue(largest_)) {
                largest_ = leftChild_;
            }
        }
        
        if (rightChild_ < heapSize_) {
            array.setState(rightChild_, Array::State::COMPARE);
            array.incrementComparisons();
            if (array.getValue(rightChild_) > array.getValue(largest_)) {
                largest_ = rightChild_;
            }
        }
        
        if (largest_ != heapifyIndex_) {
            array.setState(heapifyIndex_, Array::State::SWAP);
            array.setState(largest_, Array::State::SWAP);
            
            float temp = array.getValue(heapifyIndex_);
            array.setValue(heapifyIndex_, array.getValue(largest_));
            array.setValue(largest_, temp);
            array.incrementSwaps();
            
            heapifyIndex_ = largest_;
        } else {
            if (phase_ == Phase::HEAPIFY_DOWN) {
                buildIndex_--;
                phase_ = Phase::BUILDING_HEAP;
            } else {
                phase_ = Phase::EXTRACTING;
            }
        }
    } 
    else if (phase_ == Phase::EXTRACTING) {
        if (extractIndex_ <= 0) {
            array.resetStates();
            for (int k = 0; k < n_; ++k) {
                array.setState(k, Array::State::SORTED);
            }
            finished_ = true;
            return;
        }
        phase_ = Phase::EXTRACT_SWAP;
    } 
    else if (phase_ == Phase::EXTRACT_SWAP) {
        array.resetStates();
        array.setState(0, Array::State::SWAP);
        array.setState(extractIndex_, Array::State::SWAP);
        
        float temp = array.getValue(0);
        array.setValue(0, array.getValue(extractIndex_));
        array.setValue(extractIndex_, temp);
        array.incrementSwaps();
        
        heapSize_--;
        extractIndex_--;
        heapifyIndex_ = 0;
        phase_ = Phase::EXTRACT_HEAPIFY;
    }
}

bool HeapSorter::isFinished() const {
    return finished_;
}

std::string HeapSorter::getName() const {
    return "Heap Sort";
}

std::string HeapSorter::getTimeComplexity() const {
    return "O(n log n)";
}

std::string HeapSorter::getSpaceComplexity() const {
    return "O(1)";
}

void HeapSorter::reset() {
    n_ = 0;
    heapSize_ = 0;
    buildIndex_ = 0;
    extractIndex_ = 0;
    heapifyIndex_ = 0;
    leftChild_ = 0;
    rightChild_ = 0;
    largest_ = 0;
    finished_ = false;
    phase_ = Phase::BUILDING_HEAP;
    needSwap_ = false;
}
