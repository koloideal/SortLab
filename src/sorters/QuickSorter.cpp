#include "sorters/QuickSorter.hpp"

QuickSorter::QuickSorter()
    : currentLow_(0), currentHigh_(0), pivotIndex_(0), i_(0), j_(0)
    , pivotValue_(0.0f), finished_(false), phase_(Phase::PARTITIONING), n_(0) {
}

void QuickSorter::step(Array& array) {
    if (finished_) {
        return;
    }
    
    if (n_ == 0) {
        n_ = array.getSize();
        stack_.push_back({0, n_ - 1});
    }
    
    if (stack_.empty()) {
        array.resetStates();
        for (int k = 0; k < n_; ++k) {
            array.setState(k, Array::State::SORTED);
        }
        finished_ = true;
        return;
    }
    
    if (phase_ == Phase::PARTITIONING) {
        if (j_ == currentLow_) {
            Range range = stack_.back();
            stack_.pop_back();
            
            if (range.low >= range.high) {
                if (stack_.empty()) {
                    array.resetStates();
                    for (int k = 0; k < n_; ++k) {
                        array.setState(k, Array::State::SORTED);
                    }
                    finished_ = true;
                }
                return;
            }
            
            currentLow_ = range.low;
            currentHigh_ = range.high;
            pivotIndex_ = currentHigh_;
            pivotValue_ = array.getValue(pivotIndex_);
            i_ = currentLow_ - 1;
            j_ = currentLow_;
        }
        
        if (j_ < currentHigh_) {
            array.resetStates();
            array.setState(j_, Array::State::COMPARE);
            array.setState(pivotIndex_, Array::State::SWAP);
            
            array.incrementComparisons();
            
            if (array.getValue(j_) < pivotValue_) {
                i_++;
                
                if (i_ != j_) {
                    array.setState(i_, Array::State::SWAP);
                    
                    float temp = array.getValue(i_);
                    array.setValue(i_, array.getValue(j_));
                    array.setValue(j_, temp);
                    
                    array.incrementSwaps();
                }
            }
            
            j_++;
        } else {
            phase_ = Phase::SWAPPING_PIVOT;
        }
    } else if (phase_ == Phase::SWAPPING_PIVOT) {
        array.resetStates();
        array.setState(i_ + 1, Array::State::SWAP);
        array.setState(pivotIndex_, Array::State::SWAP);
        
        float temp = array.getValue(i_ + 1);
        array.setValue(i_ + 1, array.getValue(pivotIndex_));
        array.setValue(pivotIndex_, temp);
        
        array.incrementSwaps();
        pivotIndex_ = i_ + 1;
        
        phase_ = Phase::PUSHING_RANGES;
    } else if (phase_ == Phase::PUSHING_RANGES) {
        if (pivotIndex_ - 1 > currentLow_) {
            stack_.push_back({currentLow_, pivotIndex_ - 1});
        }
        
        if (pivotIndex_ + 1 < currentHigh_) {
            stack_.push_back({pivotIndex_ + 1, currentHigh_});
        }
        
        j_ = currentLow_;
        phase_ = Phase::PARTITIONING;
    }
}

bool QuickSorter::isFinished() const {
    return finished_;
}

std::string QuickSorter::getName() const {
    return "Quick Sort";
}

void QuickSorter::reset() {
    stack_.clear();
    currentLow_ = 0;
    currentHigh_ = 0;
    pivotIndex_ = 0;
    i_ = 0;
    j_ = 0;
    pivotValue_ = 0.0f;
    finished_ = false;
    phase_ = Phase::PARTITIONING;
    n_ = 0;
}
