#pragma once
#include "Transport.h"

class Bus : public Transport
{

    int _capacity;
    int _current;

public:
    Bus(string ID, string location, int range, string time, int cost, int current, int capacity);

private:
    bool isFull();

public:
    // ** Tại đây, hàm cancel có kiểu trả về bool vì: một số trường hợp, chúng ta không thể hủy vé (giới hạn thời gian hủy vé).
    // ?? Nhưng hiện tại chúng ta xem như nó không có cơ chế giới hạn thời gian hủy vé.

    bool book();
    bool cancel();
    bool checkAvailable();
    void getInfo(json& j);
    vector<string> info();
};
