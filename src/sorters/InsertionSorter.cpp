#include "sorters/InsertionSorter.hpp"

InsertionSorter::InsertionSorter()
    : i_(1), j_(0), n_(0), key_(0.0f), finished_(false), phase_(Phase::COMPARING) {
}

void InsertionSorter::step(Array& array) {
    if (finished_) {
        return;
    }
    
    if (n_ == 0) {
        n_ = array.getSize();
        array.setState(0, Array::State::SORTED);
    }
    
    if (phase_ == Phase::COMPARING) {
        if (i_ >= n_) {
            array.resetStates();
            for (int k = 0; k < n_; ++k) {
                array.setState(k, Array::State::SORTED);
            }
            finished_ = true;
            return;
        }
        
        key_ = array.getValue(i_);
        j_ = i_ - 1;
        phase_ = Phase::SHIFTING;
    } else if (phase_ == Phase::SHIFTING) {
        if (j_ >= 0) {
            array.resetStates();
            array.setState(j_, Array::State::COMPARE);
            array.setState(j_ + 1, Array::State::SWAP);
            
            array.incrementComparisons();
            
            if (array.getValue(j_) > key_) {
                array.setValue(j_ + 1, array.getValue(j_));
                array.incrementSwaps();
                j_--;
            } else {
                phase_ = Phase::INSERTING;
            }
        } else {
            phase_ = Phase::INSERTING;
        }
    } else if (phase_ == Phase::INSERTING) {
        array.setValue(j_ + 1, key_);
        
        for (int k = 0; k <= i_; ++k) {
            array.setState(k, Array::State::SORTED);
        }
        
        phase_ = Phase::NEXT;
    } else if (phase_ == Phase::NEXT) {
        i_++;
        phase_ = Phase::COMPARING;
    }
}

bool InsertionSorter::isFinished() const {
    return finished_;
}

std::string InsertionSorter::getName() const {
    return "Insertion Sort";
}

std::string InsertionSorter::getTimeComplexity() const {
    return "O(n) / O(n^2) / O(n^2)";
}

std::string InsertionSorter::getSpaceComplexity() const {
    return "O(1)";
}

void InsertionSorter::reset() {
    i_ = 1;
    j_ = 0;
    n_ = 0;
    key_ = 0.0f;
    finished_ = false;
    phase_ = Phase::COMPARING;
}
