#include "Bus.h"

Bus::Bus(string ID, string location, int range, string time, int cost, int current, int capacity)
    : Transport(ID, location, range, time, cost, "BUS")
{
    this->_capacity = capacity;
    this->_current = current;
}
bool Bus::isFull()
{
    if (this->_current >= this->_capacity)
        return true;
    return false;
}

// ** Tại đây, hàm cancel có kiểu trả về bool vì: một số trường hợp, chúng ta không thể hủy vé (giới hạn thời gian hủy vé).
// ?? Nhưng hiện tại chúng ta xem như nó không có cơ chế giới hạn thời gian hủy vé.

bool Bus::book()
{
    if (this->isFull())
        return false;
    this->_current++;
    return true;
}
bool Bus::cancel()
{
    if (this->_current <= 0)
        return false;
    this->_current--;
    return true;
}
bool Bus::checkAvailable()
{
    if (this->isFull())
        return false;
    return true;
}
void Bus::getInfo(json &j)
{
    json k;
    this->getBasicInfo(k);
    k["Current"] = this->_current;
    j.push_back(k);
}

vector<string> Bus::info() {
    vector<string> res;
    res.push_back(_type);
    res.push_back(to_string(_cost));
    res.push_back(_ID);
    res.push_back(to_string(_range));
    res.push_back(_location);
    return res;
}
