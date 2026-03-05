#include "SortHistory.hpp"
#include <limits>

SortHistory::SortHistory() {
}

void SortHistory::add(const SortRecord& record) {
    records_.push_back(record);
    if (records_.size() > MAX_RECORDS) {
        records_.pop_front();
    }
    
    float minNormalizedTime = std::numeric_limits<float>::max();
    for (const auto& rec : records_) {
        if (rec.normalizedTime < minNormalizedTime) {
            minNormalizedTime = rec.normalizedTime;
        }
    }
    
    for (auto& rec : records_) {
        rec.relativeSpeed = rec.normalizedTime / minNormalizedTime;
    }
}

const std::deque<SortRecord>& SortHistory::getRecords() const {
    return records_;
}

void SortHistory::clear() {
    records_.clear();
}
