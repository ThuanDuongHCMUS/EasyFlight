#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<vector>
#include"../LIB.h"
using namespace std;

class Hotel
{
	string _name;
	string _location;
	int _roomLeft;
	int _cost;	
    string _ID;
    int _capacity;

public:
    string _imgPath; // for UI
    vector<string> info();//general information
	bool book(int amount);
    Hotel(const Hotel& other, int amount);
    Hotel(string name, string location, string ID, int roomLeft, int cost, int capacity);
    static vector<Hotel*> showAvailable(vector<Hotel*> list, string location, int amount);
	void cancel();
    void getInfo(json&);
	friend class Facade;
};
