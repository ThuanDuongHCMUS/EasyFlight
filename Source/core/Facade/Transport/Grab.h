#pragma once
#include "Transport.h"

class Grab : public Transport
{
    // ** Tại đây có một biến current, kiểm tra Grab đã được đặt chỗ hay chưa
    bool _current;

public:
    Grab(string ID, string location, int range, string time, int cost, bool current);

public:
    // ** Tại đây, hàm cancel có kiểu trả về bool vì: một số trường hợp, chúng ta không thể hủy vé (giới hạn thời gian hủy vé).
    // ?? Nhưng hiện tại chúng ta xem như nó không có cơ chế giới hạn thời gian hủy vé.

    bool book();
    bool cancel();
    bool checkAvailable();
    bool isFull();
    void getInfo(json &j);
    vector<string> info();
};
