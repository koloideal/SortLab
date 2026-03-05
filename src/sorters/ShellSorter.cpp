#include "sorters/ShellSorter.hpp"

ShellSorter::ShellSorter() {
    reset();
}

void ShellSorter::step(Array& array) {
    if (finished_) return;
    
    if (n_ == 0) {
        n_ = array.getSize();
        gap_ = n_ / 2;
        i_ = gap_;
        phase_ = Phase::COMPARING;
    }
    
    if (gap_ == 0) {
        array.resetStates();
        for (int k = 0; k < n_; ++k) {
            array.setState(k, Array::State::SORTED);
        }
        finished_ = true;
        return;
    }
    
    if (phase_ == Phase::COMPARING) {
        if (i_ >= n_) {
            gap_ /= 2;
            i_ = gap_;
            if (gap_ == 0) {
                array.resetStates();
                for (int k = 0; k < n_; ++k) {
                    array.setState(k, Array::State::SORTED);
                }
                finished_ = true;
            }
            return;
        }
        
        temp_ = array.getValue(i_);
        j_ = i_;
        phase_ = Phase::SHIFTING;
    } else if (phase_ == Phase::SHIFTING) {
        if (j_ >= gap_) {
            array.resetStates();
            array.setState(j_, Array::State::COMPARE);
            array.setState(j_ - gap_, Array::State::COMPARE);
            array.incrementComparisons();
            
            if (array.getValue(j_ - gap_) > temp_) {
                array.setState(j_, Array::State::SWAP);
                array.setState(j_ - gap_, Array::State::SWAP);
                
                array.setValue(j_, array.getValue(j_ - gap_));
                array.incrementSwaps();
                j_ -= gap_;
            } else {
                phase_ = Phase::PLACING;
            }
        } else {
            phase_ = Phase::PLACING;
        }
    } else if (phase_ == Phase::PLACING) {
        array.resetStates();
        array.setState(j_, Array::State::SWAP);
        array.setValue(j_, temp_);
        
        i_++;
        phase_ = Phase::COMPARING;
    }
}

bool ShellSorter::isFinished() const {
    return finished_;
}

std::string ShellSorter::getName() const {
    return "Shell Sort";
}

std::string ShellSorter::getTimeComplexity() const {
    return "O(n log^2 n)";
}

std::string ShellSorter::getSpaceComplexity() const {
    return "O(1)";
}

void ShellSorter::reset() {
    n_ = 0;
    gap_ = 0;
    i_ = 0;
    j_ = 0;
    temp_ = 0.0f;
    finished_ = false;
    phase_ = Phase::COMPARING;
}
