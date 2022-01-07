#pragma once
#include "../LIB.h"
#include <sstream>
#include <iomanip>

class Time
{
private:
    int _h, _m;

public:
    Time();
    Time(string time);
    ~Time();

public:
    string toString() const;
    bool operator==(const Time &time);
    bool operator>=(const Time& time);
    Time &operator=(const Time &time);
};
