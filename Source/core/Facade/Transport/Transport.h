#pragma once
#include "../../LIB.h"
#include "../Time.h"

class Transport
{
protected:
    // ** Tại đây:  _ID là mã số của phương tiện
    // **           _locationStart là điểm đi
    // **           _locationEnd là điểm đến
    // **           _type là loại cấp bậc của phương tiện (thường, cao cấp)
    // **           _cost là chi phí

    // ?? Ta có thể thấy, grab và taxi là hai phương tiện hoạt động độc lập, thời gian di chuyển phụ thuộc vào khách hàng
    // ?? Do đó, biến _time chỉ có ở phương tiện bus.
    string _ID;
    string _location;
    int _range;
    string _time;
    int _cost;
    string _type;

public:
    Transport(string ID, string location, int range, string time, int cost, string type);
    string Type() { return _type; }

public:
    virtual bool book() = 0;
    virtual bool cancel() = 0;
    virtual bool checkAvailable() = 0;

    virtual bool isFull() = 0;
    static vector<Transport*> showAvailable(vector<Transport*> transport, string location, string time, int range);

    void getBasicInfo(json& j);
    virtual void getInfo(json& j) = 0;
    virtual vector<string> info() = 0;
//    string receipt();
    virtual ~Transport() {}
};

int calculate(string type);
