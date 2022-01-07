#include "Transport.h"

Transport::Transport(string ID, string location, int range, string time, int cost, string type)
{
    this->_ID = ID;
    this->_location = location;
    this->_range = range;
    this->_time = time;
    this->_cost = cost;
    this->_type = type;
}

//string Transport::receipt()
//{
//    string res = this->info();
//    res = res + '|';
//    res = res + this->_driver;
//    res = res + '|';
//    res = res + this->_licensePlate;
//    return res;
//}

vector<Transport*> Transport::showAvailable(vector<Transport*> transport, string location, string time, int range)
{
    vector<Transport*> res;

    for (auto item : transport) {
        if (item->isFull())
            continue;
        if (location == item->_location && range >= item->_range) {
            if (time == item->_time)// prioritize base on time
                res.insert(res.begin(), item);
            else
                res.push_back(item);
        }
    }
    return res;
}
void Transport::getBasicInfo(json& j)
{
    j["ID"] = this->_ID;
    j["location"] = this->_location;
    j["range"] = this->_range;
    j["time"] = this->_time;
    j["type"] = this->_type;
    j["cost"] = this->_cost;
}
int calculate(string type)
{
    if (type[0] == 'B')
    {
        if (type[1] == '1')
            return 20;
        else if (type[1] == '2')
            return 30;
        else
            return 50;
    }
    else if (type[0] == 'G')
    {
        return 1;
    }
    else //if (type[0] == 'T')
    {

        if (type[1] == '1')
            return 4;
        else if (type[1] == '2')
            return 5;
        else
            return 7;
    }
}
