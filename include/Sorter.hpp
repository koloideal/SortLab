#pragma once
#include "Array.hpp"
#include <string>

class Sorter {
public:
    virtual ~Sorter() = default;
    
    virtual void step(Array& array) = 0;
    virtual bool isFinished() const = 0;
    virtual std::string getName() const = 0;
    virtual void reset() = 0;
};
