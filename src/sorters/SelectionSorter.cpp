#include "sorters/SelectionSorter.hpp"

SelectionSorter::SelectionSorter()
    : i_(0), j_(0), minIndex_(0), n_(0), finished_(false), phase_(Phase::FINDING_MIN) {
}

void SelectionSorter::step(Array& array) {
    if (finished_) {
        return;
    }
    
    if (n_ == 0) {
        n_ = array.getSize();
        minIndex_ = 0;
    }
    
    if (phase_ == Phase::FINDING_MIN) {
        if (j_ == i_) {
            minIndex_ = i_;
            j_++;
        }
        
        if (j_ < n_) {
            array.resetStates();
            array.setState(i_, Array::State::COMPARE);
            array.setState(j_, Array::State::COMPARE);
            array.setState(minIndex_, Array::State::SWAP);
            
            array.incrementComparisons();
            
            if (array.getValue(j_) < array.getValue(minIndex_)) {
                minIndex_ = j_;
            }
            
            j_++;
        } else {
            phase_ = Phase::SWAPPING;
        }
    } else if (phase_ == Phase::SWAPPING) {
        if (minIndex_ != i_) {
            array.resetStates();
            array.setState(i_, Array::State::SWAP);
            array.setState(minIndex_, Array::State::SWAP);
            
            float temp = array.getValue(i_);
            array.setValue(i_, array.getValue(minIndex_));
            array.setValue(minIndex_, temp);
            
            array.incrementSwaps();
        }
        
        array.setState(i_, Array::State::SORTED);
        phase_ = Phase::NEXT;
    } else if (phase_ == Phase::NEXT) {
        i_++;
        
        if (i_ >= n_ - 1) {
            array.resetStates();
            for (int k = 0; k < n_; ++k) {
                array.setState(k, Array::State::SORTED);
            }
            finished_ = true;
            return;
        }
        
        j_ = i_;
        phase_ = Phase::FINDING_MIN;
    }
}

bool SelectionSorter::isFinished() const {
    return finished_;
}

std::string SelectionSorter::getName() const {
    return "Selection Sort";
}

void SelectionSorter::reset() {
    i_ = 0;
    j_ = 0;
    minIndex_ = 0;
    n_ = 0;
    finished_ = false;
    phase_ = Phase::FINDING_MIN;
}
