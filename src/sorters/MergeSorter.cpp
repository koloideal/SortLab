#include "sorters/MergeSorter.hpp"

MergeSorter::MergeSorter()
    : currentSize_(1), leftStart_(0), mid_(0), rightEnd_(0)
    , leftIndex_(0), rightIndex_(0), mergeIndex_(0)
    , finished_(false), phase_(Phase::MERGING), n_(0) {
}

void MergeSorter::step(Array& array) {
    if (finished_) {
        return;
    }
    
    if (n_ == 0) {
        n_ = array.getSize();
        temp_.resize(n_);
    }
    
    if (currentSize_ >= n_) {
        array.resetStates();
        for (int k = 0; k < n_; ++k) {
            array.setState(k, Array::State::SORTED);
        }
        finished_ = true;
        return;
    }
    
    if (phase_ == Phase::MERGING) {
        if (leftStart_ >= n_ - 1) {
            currentSize_ *= 2;
            leftStart_ = 0;
            return;
        }
        
        mid_ = leftStart_ + currentSize_ - 1;
        rightEnd_ = (leftStart_ + 2 * currentSize_ - 1 < n_ - 1) 
                    ? leftStart_ + 2 * currentSize_ - 1 
                    : n_ - 1;
        
        if (mid_ >= n_) {
            mid_ = n_ - 1;
        }
        
        leftIndex_ = leftStart_;
        rightIndex_ = mid_ + 1;
        mergeIndex_ = 0;
        
        for (int k = leftStart_; k <= rightEnd_; ++k) {
            temp_[mergeIndex_++] = array.getValue(k);
        }
        
        leftIndex_ = 0;
        rightIndex_ = mid_ - leftStart_ + 1;
        mergeIndex_ = leftStart_;
        
        phase_ = Phase::COPYING_BACK;
    } else if (phase_ == Phase::COPYING_BACK) {
        int leftEnd = mid_ - leftStart_;
        int rightEndLocal = rightEnd_ - leftStart_;
        
        if (leftIndex_ <= leftEnd && rightIndex_ <= rightEndLocal) {
            array.resetStates();
            array.setState(mergeIndex_, Array::State::SWAP);
            array.setState(leftStart_ + leftIndex_, Array::State::COMPARE);
            array.setState(leftStart_ + rightIndex_, Array::State::COMPARE);
            
            array.incrementComparisons();
            
            if (temp_[leftIndex_] <= temp_[rightIndex_]) {
                array.setValue(mergeIndex_, temp_[leftIndex_]);
                leftIndex_++;
            } else {
                array.setValue(mergeIndex_, temp_[rightIndex_]);
                rightIndex_++;
            }
            
            array.incrementSwaps();
            mergeIndex_++;
        } else {
            phase_ = Phase::COPYING_LEFT;
        }
    } else if (phase_ == Phase::COPYING_LEFT) {
        int leftEnd = mid_ - leftStart_;
        
        if (leftIndex_ <= leftEnd) {
            array.resetStates();
            array.setState(mergeIndex_, Array::State::SWAP);
            
            array.setValue(mergeIndex_, temp_[leftIndex_]);
            leftIndex_++;
            mergeIndex_++;
            array.incrementSwaps();
        } else {
            phase_ = Phase::COPYING_RIGHT;
        }
    } else if (phase_ == Phase::COPYING_RIGHT) {
        int rightEndLocal = rightEnd_ - leftStart_;
        
        if (rightIndex_ <= rightEndLocal) {
            array.resetStates();
            array.setState(mergeIndex_, Array::State::SWAP);
            
            array.setValue(mergeIndex_, temp_[rightIndex_]);
            rightIndex_++;
            mergeIndex_++;
            array.incrementSwaps();
        } else {
            phase_ = Phase::NEXT_MERGE;
        }
    } else if (phase_ == Phase::NEXT_MERGE) {
        leftStart_ += 2 * currentSize_;
        phase_ = Phase::MERGING;
    }
}

bool MergeSorter::isFinished() const {
    return finished_;
}

std::string MergeSorter::getName() const {
    return "Merge Sort";
}

std::string MergeSorter::getTimeComplexity() const {
    return "O(n log n) / O(n log n) / O(n log n)";
}

std::string MergeSorter::getSpaceComplexity() const {
    return "O(n)";
}

void MergeSorter::reset() {
    currentSize_ = 1;
    leftStart_ = 0;
    mid_ = 0;
    rightEnd_ = 0;
    leftIndex_ = 0;
    rightIndex_ = 0;
    mergeIndex_ = 0;
    temp_.clear();
    finished_ = false;
    phase_ = Phase::MERGING;
    n_ = 0;
}
