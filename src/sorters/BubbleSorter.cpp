#include "sorters/BubbleSorter.hpp"

BubbleSorter::BubbleSorter() 
    : i_(0), j_(0), n_(0), finished_(false), phase_(Phase::COMPARING) {
}

void BubbleSorter::step(Array& array) {
    if (finished_) {
        return;
    }
    
    if (n_ == 0) {
        n_ = array.getSize();
    }
    
    if (phase_ == Phase::COMPARING) {
        if (j_ >= n_ - i_ - 1) {
            i_++;
            j_ = 0;
            
            if (i_ >= n_ - 1) {
                array.resetStates();
                for (int k = 0; k < n_; ++k) {
                    array.setState(k, Array::State::SORTED);
                }
                finished_ = true;
                return;
            }
        }
        
        array.resetStates();
        array.setState(j_, Array::State::COMPARE);
        array.setState(j_ + 1, Array::State::COMPARE);
        
        array.incrementComparisons();
        
        if (array.getValue(j_) > array.getValue(j_ + 1)) {
            phase_ = Phase::SWAPPING;
        } else {
            phase_ = Phase::NEXT;
        }
    } else if (phase_ == Phase::SWAPPING) {
        array.setState(j_, Array::State::SWAP);
        array.setState(j_ + 1, Array::State::SWAP);
        
        float temp = array.getValue(j_);
        array.setValue(j_, array.getValue(j_ + 1));
        array.setValue(j_ + 1, temp);
        
        array.incrementSwaps();
        phase_ = Phase::NEXT;
    } else if (phase_ == Phase::NEXT) {
        j_++;
        phase_ = Phase::COMPARING;
    }
}

bool BubbleSorter::isFinished() const {
    return finished_;
}

std::string BubbleSorter::getName() const {
    return "Bubble Sort";
}

std::string BubbleSorter::getTimeComplexity() const {
    return "O(n) / O(n^2) / O(n^2)";
}

std::string BubbleSorter::getSpaceComplexity() const {
    return "O(1)";
}

void BubbleSorter::reset() {
    i_ = 0;
    j_ = 0;
    n_ = 0;
    finished_ = false;
    phase_ = Phase::COMPARING;
}
