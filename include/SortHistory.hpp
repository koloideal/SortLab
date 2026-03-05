#pragma once
#include <string>
#include <deque>

struct SortRecord {
    std::string algorithmName;
    int arraySize;
    int comparisons;
    int swaps;
    float normalizedTime;
    float relativeSpeed;
    
    SortRecord() : arraySize(0), comparisons(0), swaps(0), normalizedTime(0.0f), relativeSpeed(1.0f) {}
};

class SortHistory {
public:
    SortHistory();
    
    void add(const SortRecord& record);
    const std::deque<SortRecord>& getRecords() const;
    void clear();

private:
    std::deque<SortRecord> records_;
    static const size_t MAX_RECORDS = 20;
};
