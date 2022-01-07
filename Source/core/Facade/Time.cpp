#include "Time.h"

Time::Time()
{
}
Time::Time(string datetime)
{
    _h = (datetime[8] - '0') * 10 + (datetime[9] - '0');
    _m = (datetime[10] - '0') * 10 + (datetime[11] - '0');
}
Time::~Time()
{
}

string Time::toString() const {
    stringstream writer;
    writer << setw(2) << setfill('0') << _h << ":";
    writer << setw(2) << setfill('0') << _m;
    return writer.str();
}

bool Time::operator==(const Time &time)
{
    if (this->_h == time._h && this->_m == time._m)
        return true;
    return false;
}
bool Time::operator>=(const Time& time) {
    return _h >= time._h || (_h == time._h && _m >= time._m);
}
Time &Time::operator=(const Time &time)
{
    this->_h = time._h;
    this->_m = time._m;
    return *this;
}
