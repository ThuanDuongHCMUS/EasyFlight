#include "../LIB.h"
#include"Date.h"
#include"Time.h"
#include <vector>
using namespace std;

class Flight
{
public:
	class Ticket
	{
	private:
        int _fare = 0;
        Flight* _flight = nullptr;// correspodent flight
	public:
		bool _isBooked;
        Ticket(Flight* flight);
        Ticket(const Ticket& ip);
		bool book();
        int fare() { return _fare; }
		void cancel();
        void getInfo(json &j);
        vector<string> info();
		~Ticket();
	};
    Flight(string _depApr, string _arrApr, string depTime, string arrTime, string name, int seatLeft, string ID, int capascity, int fare);
	Flight(const Flight& ip);
    vector<string> info();
    Ticket* book();
    void getInfo(json&);
    static vector<Flight*> showAvailable(vector<Flight*> list, string dep, string arr, string depT, string curT);
private:
	string _arrApr;// arrival airport
	string _depApr;// departure airport
    string _depTime;// departure time
    string _arrTime;// arrival time
	string _name;	
	int _seatLeft;	
    int _capacity;
    string _ID;
    int _fare;
};
