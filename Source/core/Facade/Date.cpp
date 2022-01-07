#include "Date.h"

Date::Date()
{
}
Date::Date(string datetime)
{
    _day = stoi(datetime.substr(0, 2));
    _month = stoi(datetime.substr(2, 4));
    _year = stoi(datetime.substr(4, 4));
}
Date::~Date()
{
}

string Date::toString() const {
    stringstream writer;
    writer << setw(2) << setfill('0') << _day << "/";
    writer << setw(2) << setfill('0') << _month << "/";
    writer << setw(4) << setfill('0') << _year;
    return writer.str();
}
bool Date::operator==(const Date &time)
{
    if (this->_day == time._day && this->_month == time._month && this->_year == time._year)
        return true;
    return false;
}
bool Date::operator>=(const Date& date) {
    return _year >= date._year
            || (_year == date._year && _month >= date._month)
            || (_year == date._year && _month == date._month && _day >= date._day);
}
Date &Date::operator=(const Date &time)
{
    _day = time._day;
    _month = time._month;
    _year = time._year;
    return *this;
}
