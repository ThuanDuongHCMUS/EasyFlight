#define _CRT_SECURE_NO_WARNINGS
#include"Flight.h"
#include<iostream>

Flight::Flight(string _depApr, string _arrApr, string depTime, string arrTime, string name, int seatLeft, string ID, int capacity, int fare)
{
	this->_depApr = _depApr;
	this->_arrApr = _arrApr;
    this->_depTime = depTime;
    this->_arrTime = arrTime;
    this->_name = name;
    this->_seatLeft = seatLeft;
    this->_ID = ID;
    this->_capacity = capacity;
    this->_fare = fare;
}

Flight::Flight(const Flight& ip)
{
	_depApr = ip._depApr;
	_arrApr = ip._arrApr;
    _depTime = ip._depTime;
	_name = ip._name;
    _seatLeft = ip._seatLeft;
    _arrTime = ip._arrTime;
    _ID = ip._ID;
    _capacity = ip._capacity;
    _fare = ip._fare;
}

// arrA, depA, arrT, depT, fare
vector<string> Flight::info()
{
    vector<string> res;
    res.push_back(_arrApr);
    res.push_back(_depApr);
    res.push_back(_arrTime);
    res.push_back(_depTime);
    res.push_back(to_string(_fare));
    return res;
}

Flight::Ticket* Flight::book()
{
	Flight::Ticket* res = nullptr;
	if (_seatLeft > 0) {
        res = new Ticket(this);
		_seatLeft--;
	}		
	return res;
}

void Flight::getInfo(json &j)
{
    json k;
    k["ArrivalAirport"] = this->_arrApr;
    k["ArrivalTime"] = this->_arrTime;
    k["DepartureAirport"] = this->_depApr;
    k["DepartureTime"] = this->_depTime;
    k["capacity"] = this->_capacity;
    k["current"] = _capacity - _seatLeft;
    k["id"] = this->_ID;
    k["name"] = this->_name;
    k["fare"] = _fare;

    j.push_back(k);
}

vector<Flight*> Flight::showAvailable(vector<Flight*> list, string dep, string arr, string depT, string curT)
{
    vector<Flight*> res;
    for (auto item : list) {

        if (item->_depApr == dep && item->_arrApr == arr
                && Date(item->_depTime) == Date(depT)
                && Date(item->_depTime) >= Date(curT)
                )
        {

            if (Time(item->_depTime) == Time(depT))// prioritze time
                res.insert(res.begin(), item);
			else
                res.push_back(item);
        }
    }
	return res;
}

Flight::Ticket::Ticket(Flight* flight)
{
    this->_fare = flight->_fare;
	this->_isBooked = false;
	this->_flight = flight;	
}

Flight::Ticket::Ticket(const Ticket& ip)
{
	_fare = ip._fare;
	_isBooked = ip._isBooked;
	_flight = ip._flight;	
}

bool Flight::Ticket::book()
{
	if (!_isBooked)
		return true;
	return false;
}

void Flight::Ticket::cancel()
{
	_flight->_seatLeft++;	
}

// void Flight::Ticket::operator=(Flight::Ticket& ip)
// {
// 	_fare = ip._fare;
// 	_isBooked = ip._isBooked;
// 	_flight = ip._flight;	
// }

void Flight::Ticket::getInfo(json &j) {
    json k;

    k["ArrivalAirport"] = this->_flight->_arrApr;
    k["DepartureAirport"] = this->_flight->_depApr;
    k["ArrivalTime"] = this->_flight->_arrTime;
    k["DepartureTime"] = this->_flight->_depTime;
    k["id"] = this->_flight->_ID;
    k["fare"] = this->_fare;
    k["name"] = this->_flight->_name;

    j.push_back(k);
}

vector<string> Flight::Ticket::info() {
    return _flight->info();
}

Flight::Ticket::~Ticket()
{
	delete _flight;
}
