#include "Taxi.h"

Taxi::Taxi(string ID, string location, int range, string time, int cost, bool current)
    : Transport(ID, location, range, time, cost, "TAXI")
{
    this->_current = current;
}

bool Taxi::book()
{
    if (this->_current == true)
        return 0;

    this->_current = true;
    return 1;
}
bool Taxi::cancel()
{
    this->_current = false;
    return 1;
}
bool Taxi::checkAvailable()
{
    // ** Nếu Grab chưa được đặt, ta return 1
    if (this->_current == true)
        return 1;
    return 0;
}
bool Taxi::isFull()
{
    return this->_current;
}
void Taxi::getInfo(json &j)
{
    json k;
    this->getBasicInfo(k);
    k["current"] = this->_current;
    j.push_back(k);
}

vector<string> Taxi::info() {
    vector<string> res;
    res.push_back(_type);
    res.push_back(to_string(_cost));
    res.push_back(_ID);
    res.push_back(to_string(_range));
    res.push_back(_location);
    return res;
}
