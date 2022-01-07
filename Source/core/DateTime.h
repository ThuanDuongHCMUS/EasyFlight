#pragma once
#include <string>
#include <time.h>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

class DateTime {
private:
    int d, m, y, h, min;
public:
    DateTime() {
        time_t t = time(0);
        tm* now = localtime(&t);
        d = now->tm_mday;
        m = now->tm_mon + 1;
        y = now->tm_year + 1900;
        h = now->tm_hour;
        min = (rand() % 11 + 1) * 5;
    }
    DateTime operator+ (const int minutes) {
        min += minutes;
        h += (min / 60); min %= 60;
        d += (h / 24); h %= 24;
        int temp = dayInMonth(m, y);
        m += (d - 1) / temp; d = (d - 1) % temp + 1;
        y += (m - 1) / 12; m = (m - 1) % 12 + 1;
        return *this;
    }
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    }
    int dayInMonth(int month, int year) {
        if (month == 2) {
            if (isLeapYear(year))
                return 29;
            else 
                return 28;
        }

        if (month == 4 || month == 6 || month == 9 || month == 11) 
            return 30;
        return 31;
    }
    string toString() {
        stringstream ss;
        ss << setw(2) << setfill('0') << d;
        ss << setw(2) << setfill('0') << m;
        ss << setw(4) << setfill('0') << y;
        ss << setw(2) << setfill('0') << h;
        ss << setw(2) << setfill('0') << min;
        return ss.str();
    }

    DateTime* Parse(string str) {
        d = (stoi(str.substr(0, 2)));
        m = (stoi(str.substr(2, 2)));
        y = (stoi(str.substr(4, 4)));
        h = (stoi(str.substr(8, 2)));
        min = (stoi(str.substr(10, 2)));
        return this;
    }
    static string ParseDate(string str) {
        string res = str.substr(0, 2) + str.substr(3, 2) + str.substr(6);
        return res;
    }
    static string ParseTime(string str) {
        string res = str.substr(0, 2) + str.substr(3);
        return res;
    }
    static string ToDate(string str) {
        string res = str.substr(0, 2) + "/" + str.substr(2, 2) + "/" + str.substr(4);
        return res;
    }
    static string ToTime(string str) {
        string res = str.substr(0, 2) + ":" + str.substr(2);
        return res;
    }
};
