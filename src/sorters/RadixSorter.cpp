#include "sorters/RadixSorter.hpp"
#include <cmath>
#include <algorithm>

RadixSorter::RadixSorter() {
    reset();
}

void RadixSorter::step(Array& array) {
    if (finished_) return;
    
    if (n_ == 0) {
        n_ = array.getSize();
        maxValue_ = 0;
        for (int k = 0; k < n_; ++k) {
            int val = static_cast<int>(std::round(std::abs(array.getValue(k))));
            if (val > maxValue_) maxValue_ = val;
        }
        if (maxValue_ == 0) maxValue_ = 1;
        exp_ = 1;
        count_.resize(10, 0);
        output_.resize(n_, 0.0f);
        phase_ = Phase::INIT;
    }
    
    if (phase_ == Phase::INIT) {
        if (exp_ > maxValue_) {
            array.resetStates();
            for (int k = 0; k < n_; ++k) {
                array.setState(k, Array::State::SORTED);
            }
            finished_ = true;
            return;
        }
        
        std::fill(count_.begin(), count_.end(), 0);
        i_ = 0;
        phase_ = Phase::COUNTING;
    } else if (phase_ == Phase::COUNTING) {
        if (i_ < n_) {
            array.resetStates();
            array.setState(i_, Array::State::COMPARE);
            
            int val = static_cast<int>(std::round(std::abs(array.getValue(i_))));
            int digit = (val / exp_) % 10;
            count_[digit]++;
            array.incrementComparisons();
            i_++;
        } else {
            for (int k = 1; k < 10; ++k) {
                count_[k] += count_[k - 1];
            }
            i_ = n_ - 1;
            phase_ = Phase::PLACING;
        }
    } else if (phase_ == Phase::PLACING) {
        if (i_ >= 0) {
            array.resetStates();
            array.setState(i_, Array::State::SWAP);
            
            int val = static_cast<int>(std::round(std::abs(array.getValue(i_))));
            int digit = (val / exp_) % 10;
            output_[count_[digit] - 1] = array.getValue(i_);
            count_[digit]--;
            array.incrementSwaps();
            i_--;
        } else {
            i_ = 0;
            phase_ = Phase::COPYING_BACK;
        }
    } else if (phase_ == Phase::COPYING_BACK) {
        if (i_ < n_) {
            array.resetStates();
            array.setState(i_, Array::State::SWAP);
            array.setValue(i_, output_[i_]);
            i_++;
        } else {
            exp_ *= 10;
            phase_ = Phase::INIT;
        }
    }
}

bool RadixSorter::isFinished() const {
    return finished_;
}

std::string RadixSorter::getName() const {
    return "Radix Sort";
}

std::string RadixSorter::getTimeComplexity() const {
    return "O(n*k)";
}

std::string RadixSorter::getSpaceComplexity() const {
    return "O(n + k)";
}

void RadixSorter::reset() {
    n_ = 0;
    maxValue_ = 0;
    exp_ = 1;
    i_ = 0;
    count_.clear();
    output_.clear();
    finished_ = false;
    phase_ = Phase::INIT;
}
