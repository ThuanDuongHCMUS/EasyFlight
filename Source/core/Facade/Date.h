#pragma once
#include "../LIB.h"
#include <sstream>
#include <iomanip>

class Date
{
private:
    int _day, _month, _year;

public:
    Date();
    Date(string datetime);
    ~Date();

public:
    string toString() const;
    bool operator==(const Date &time);
    bool operator>=(const Date& date);
    Date &operator=(const Date &time);
};
