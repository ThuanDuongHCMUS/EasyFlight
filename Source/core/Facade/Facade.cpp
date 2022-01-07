#include"Facade.h"

Facade::Facade()
{
}

void Facade::readFileJsonFlight(string address) {
    json j;
    fstream f;
    f.open(address, ios::in | ios::binary);
    if (f.fail()) {
        return;
    }
    f >> j;
    // iterate the array
    for (json::iterator it = j.begin(); it != j.end(); ++it)
    {
        string arr = it->at("ArrivalAirport");
        string dep = it->at("DepartureAirport");
        string arrT = it->at("ArrivalTime");
        string depT = it->at("DepartureTime");
        int capacity = (int)it->at("capacity");
        int seatLeft = (int)it->at("capacity") - (int)it->at("current");
        string ID = it->at("id");
        string name = it->at("name");
        int fare = it->at("fare");
        Flight* flight = new Flight(dep, arr, depT, arrT, name, seatLeft, ID, capacity, fare);
        _avaFlt.push_back(flight);
    }

    f.close();
}

void Facade::readFileJsonHotel(string address) {
    json j;
    fstream f;
    f.open(address, ios::in | ios::binary);
    if (f.fail()) {
        return;
    }
    f >> j;
    // iterate the array
    for (json::iterator it = j.begin(); it != j.end(); ++it)
    {
        string name = it->at("name");
        string location = it->at("location");
        string id = it->at("id");
        int roomLeft = (int)it->at("capacity") - (int)it->at("current");
        int capacity = it->at("capacity");
        int cost = it->at("cost");
        Hotel* hotel = new Hotel(name, location, id, roomLeft, cost, capacity);
        _avaHtl.push_back(hotel);
    }

    f.close();
}

void Facade::readFileJsonTransport(string address, int type) {
    json j;
    fstream f;
    f.open(address, ios::in | ios::binary);
    if (f.fail()) {
        return;
    }
    f >> j;
    // iterate the array
    if (type == 0) {
        for (json::iterator it = j.begin(); it != j.end(); ++it)
        {
            string ID = it->at("ID");
            double cost = it->at("cost");
            int current = it->at("current");
            string location = it->at("location");
            int range = it->at("range");
            string time = it->at("time");
            _avaTrs.push_back(new Taxi(ID, location, range, time, cost, current));
        }
    }
    else if (type == 1) {
        for (json::iterator it = j.begin(); it != j.end(); ++it)
        {
            string ID = it->at("ID");
            double cost = it->at("cost");
            int current = it->at("current");
            int capacity = it->at("capacity");
            string location = it->at("location");
            int range = it->at("range");
            string time = it->at("time");
            _avaTrs.push_back(new Bus(ID, location, range, time, cost, current, capacity));
        }
    }
    else {
        for (json::iterator it = j.begin(); it != j.end(); ++it)
        {
            string ID = it->at("ID");
            double cost = it->at("cost");
            int current = it->at("current");
            string location = it->at("location");
            int range = it->at("range");
            string time = it->at("time");
            _avaTrs.push_back(new Grab(ID, location, range, time, cost, current));
        }
    }
    f.close();
}

vector<Ticket*> Facade::bookTicket(string dep, string arr, string depTime, string depTimeR, string curTime, vector<int> choices, bool isTwoWay)
{
    vector<Ticket*> res;
    vector<Flight*> filtered = Flight::showAvailable(_avaFlt, dep, arr, depTime, curTime);// showAvailable the flights

    Flight* choseFlt = filtered[choices[0]];

    Ticket* choseSeat = choseFlt->book();
    if (choseSeat) {
        _bkdTck.push_back(choseSeat);
        res.push_back(choseSeat);
    }

    if(isTwoWay){
        vector<Flight*> filtered = Flight::showAvailable(_avaFlt, arr, dep, depTimeR, curTime);// showAvailable the flights

        Flight* choseFlt = _avaFlt[choices[1]];

        Ticket* choseSeat = choseFlt->book();
        if (choseSeat) {
            _bkdTck.push_back(choseSeat);
            res.push_back(choseSeat);
        }

    }
    return res;
}



vector<Transport*> Facade::bookTransport(string location, string time, int range, int choice)
{
    vector<Transport*> res;
    vector<Transport*> filtered = Transport::showAvailable(_avaTrs, location, time, range);
    Transport* chosetrs = filtered[choice];

    bool buffer = chosetrs->book();
    if (buffer) {
        _bkdTrs.push_back(chosetrs);
        res.push_back(chosetrs);
    }

    return res;
}

vector<Hotel*> Facade::bookHotel(string location, int choice, int amount)
{
    vector<Hotel*> res;
    vector<Hotel*> filtered = Hotel::showAvailable(_avaHtl, location, amount);

    Hotel* choseHtl = filtered[choice];

    bool buffer = choseHtl->book(amount);
    if (buffer) {
        _bkdHtl.push_back(choseHtl);
        res.push_back(choseHtl);
    }

    return res;
}

vector<Flight*> Facade::availableFlight(string dep, string arr, string departureTime, string currentTime) {
    return Flight::showAvailable(_avaFlt, dep, arr, departureTime, currentTime);
}

vector<Hotel*> Facade::availableHotel(string location, int amount) {
    return Hotel::showAvailable(_avaHtl, location, amount);
}

vector<Transport*> Facade::availableTransport(string time, string location, int range) {
    return Transport::showAvailable(_avaTrs, location, time, range);
}

void Facade::cancelTrs(int index)
{	
	if (index >= _bkdTrs.size())
		return;
	_bkdTrs[index]->cancel();
    _bkdTrs[index] = nullptr;
	_bkdTrs.erase(next(_bkdTrs.begin(), index));
}

void Facade::cancelHtl(int index)
{
	if (index >= _bkdHtl.size())
		return;
	_bkdHtl[index]->cancel();
    _bkdHtl[index] = nullptr;
	_bkdHtl.erase(next(_bkdHtl.begin(), index));
}

void Facade::cancelTck(int index)
{
	if (index >= _bkdTck.size())
		return;
    _bkdTck[index]->cancel();
    _bkdTck[index] = nullptr;
	_bkdTck.erase(next(_bkdTck.begin(), index));
}

void Facade::delBooked() {
    for (int i = 0; i < _bkdTck.size(); ++i)
        _bkdTck[i] = nullptr;
    for (int i = 0; i < _bkdHtl.size(); ++i)
        _bkdHtl[i] = nullptr;
    for (int i = 0; i < _bkdTrs.size(); ++i)
        _bkdTrs[i] = nullptr;
    _bkdTck.clear();
    _bkdHtl.clear();
    _bkdTrs.clear();
}

Facade::~Facade()
{
    delBooked();
    for (int i = 0; i < _avaFlt.size(); ++i)
        delete _avaFlt[i];
    for (int i = 0; i < _avaHtl.size(); ++i)
        delete _avaHtl[i];
    for (int i = 0; i < _avaTrs.size(); ++i)
        delete _avaTrs[i];
}

void Facade::readFileJsonUserBooked(string address)
{
    json j;
    fstream f;
    f.open(address, ios::in | ios::binary);
    if (f.fail())
        return;

    f >> j;

    json hotels;
    hotels = j["hotels"];
    if (hotels != nullptr)
        for (auto it = hotels.begin(); it != hotels.end(); ++it) {
            string name = it->at("name");
            string location = it->at("location");
            string id = it->at("id");
            int capacity = it->at("capacity");
            int roomLeft = capacity - (int)it->at("current");
            int cost = it->at("cost");

            this->_bkdHtl.push_back(new Hotel(name, location, id, roomLeft, cost, capacity));
        }

    json tik;
    tik = j.at("tickets");
    if (tik != nullptr)
        for (auto it = tik.begin(); it != tik.end(); ++it) {
            string arr = it->at("ArrivalAirport");
            string dep = it->at("DepartureAirport");
            string arrT = it->at("ArrivalTime");
            string depT = it->at("DepartureTime");
            string ID = it->at("id");
            string name = it->at("name");
            int fare = it->at("fare");
            this->_bkdTck.push_back(new Ticket(new Flight(dep, arr, depT, arrT, name, 0, ID, 0, fare)));
        }



    json trans;
    trans = j.at("transports");
    if (trans != nullptr)
        for(auto it = trans.begin(); it != trans.end(); ++it) {
            string type = it->at("type");
            string location = it->at("location");
            string ID = it->at("ID");
            string time = it->at("time");
            int cost = it->at("cost");
            if (type == "BUS") {
                _bkdTrs.push_back(new Bus(ID, location, 0, time, cost, 0, 0));
            }
            else if (type == "TAXI") {
                _bkdTrs.push_back(new Taxi(ID, location, 0, time, cost, 0));
            }
            else { // type == "GRAB"
                _bkdTrs.push_back(new Grab(ID, location, 0, time, cost, 0));
            }
        }

    f.close();
}

void Facade::updateAvailableUserBooked(string address)
{
    fstream f;
    f.open(address, ios::out | ios::binary);

    json j;

    json tik;
    for (auto itr = this->_bkdTck.begin(); itr != this->_bkdTck.end(); itr++)
        (*itr)->getInfo(tik);

    json hotels;
    for (auto itr = this->_bkdHtl.begin(); itr != this->_bkdHtl.end(); itr++)
        (*itr)->getInfo(hotels);

    json trans;
    for (auto itr = this->_bkdTrs.begin(); itr != this->_bkdTrs.end(); itr++)
        (*itr)->getInfo(trans);

    j["tickets"] = tik;
    j["hotels"] = hotels;
    j["transports"] = trans;

    f << setw(4) << j;
    f.close();
}

void Facade::updateAvailableHotel(string address)
{
    fstream f;
    f.open(address, ios::out | ios::binary);

    json j;
    for (auto itr = this->_avaHtl.begin(); itr != this->_avaHtl.end(); itr++)
        (*itr)->getInfo(j);

    f << setw(4) << j;
    f.close();
}

void Facade::updateAvailableTransport(string grabPath, string busPath, string taxiPath)
{
    json jTaxi, jBus, jGrab;
    fstream fTaxi, fBus, fGrab;

    // Open taxi.json
    fTaxi.open(taxiPath, ios::in | ios::binary);

    // Open bus.json
    fBus.open(busPath, ios::in | ios::binary);

    // Open grab.json
    fGrab.open(grabPath, ios::in | ios::binary);

    for (auto trs : _avaTrs) {
        if (trs->Type() == "BUS") {
            trs->getInfo(jBus);
        }
        else if (trs->Type() == "GRAB") {
            trs->getInfo(jGrab);
        }
        else { // trs->Type() == "TAXI"
            trs->getInfo(jTaxi);
        }
    }

    fBus << setw(4) << jBus;
    fTaxi << setw(4) << jTaxi;
    fGrab << setw(4) << jGrab;
    fBus.close();
    fTaxi.close();
    fGrab.close();
}

void Facade::updateAvailableFlight(string address)
{
    fstream f;
    f.open(address, ios::out | ios::binary);

    json j;
    for (auto itr = this->_avaFlt.begin(); itr != this->_avaFlt.end(); itr++)
        (*itr)->getInfo(j);

    f << setw(4) << j;
    f.close();
}
