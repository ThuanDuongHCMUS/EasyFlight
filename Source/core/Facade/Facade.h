#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include"Transport/Bus.h"
#include "Transport/Grab.h"
#include "Transport/Taxi.h"
#include"Hotel.h"
#include"Flight.h"
#include"Time.h"
#include "../LIB.h"

using namespace std;
typedef Flight::Ticket Ticket;

class Facade
{	
	// database
	vector<Flight* > _avaFlt;// available flight
	vector<Hotel*> _avaHtl;// available hotels
	vector<Transport*> _avaTrs;// available transports
public:
	vector<Ticket*> _bkdTck;// booked tickets
	vector<Hotel*> _bkdHtl;// booked hotels
	vector<Transport*> _bkdTrs;// booked transport
	
public:	
    Facade();
    void readFileJsonFlight(string address);
    void readFileJsonHotel(string address);

    // 0: taxi, 1: bus, khac: grab
    void readFileJsonTransport(string address, int type);

    vector<Ticket*> bookTicket(string dep, string arr, string depTime, string depTimeR, string curTime, vector<int> choices, bool isTwoWay);
    vector<Transport*> bookTransport(string location, string time, int range, int choice);
    vector<Hotel*> bookHotel(string location, int choice, int amount);

    vector<Flight*> availableFlight(string dep, string arr, string departureTime, string currentTime);
    vector<Hotel*> availableHotel(string location, int amount);
    vector<Transport*> availableTransport(string time, string location, int range);

	void cancelTrs(int index);
	void cancelHtl(int index);
	void cancelTck(int index);

    void delBooked();
	~Facade();

    void readFileJsonUserBooked(string address);
    void updateAvailableUserBooked(string address);

    void updateAvailableHotel(string address);
    void updateAvailableTransport(string grabPath, string busPath, string taxiPath);
    void updateAvailableFlight(string address);
};
