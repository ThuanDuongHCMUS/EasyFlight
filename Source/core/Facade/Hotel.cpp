#include"Hotel.h"

vector<string> Hotel::info()
{
    vector<string> res;
    res.push_back(_name);
    res.push_back(_location);
    res.push_back(to_string(_roomLeft));
    res.push_back(to_string(_cost));
    res.push_back(_imgPath);
    return res;
}

bool Hotel::book(int amount)
{
	if (amount > _roomLeft)
		return false;
	_roomLeft -= amount;
	return true;
}

Hotel::Hotel(const Hotel& other, int amount) {
    _name = other._name;
    _location = other._location;
    _roomLeft = amount;
    _cost = other._cost * amount;
    _ID = other._ID;
    _capacity = other._capacity;
    _imgPath = other._imgPath;
}

Hotel::Hotel(string name, string location, string ID, int roomLeft, int cost, int capacity) {
    _name = name;
    _location = location;
    _roomLeft = roomLeft;
    _cost = cost;
    _ID = ID;
    _capacity = capacity;
    _imgPath = "../img/hotels/" + _ID + ".png";
}

vector<Hotel*> Hotel::showAvailable(vector<Hotel*> list, string location, int amount)
{
    vector<Hotel*> res;
	for (auto item : list)
        if (item->_location == location && item->_roomLeft >= amount)
            res.push_back(item);
	return res;
}

void Hotel::cancel()
{
	this->_roomLeft++;
}

void Hotel::getInfo(json &j) {
    json k;

    k["id"] = this->_ID;
    k["name"] = this->_name;
    k["location"] = this->_location;
    k["cost"] = this->_cost;
    k["current"] = _capacity - _roomLeft;
    k["capacity"] = _capacity;

    j.push_back(k);
}
