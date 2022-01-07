#pragma once
#include "LIB.h"
class Account
{
public:
    static int _num;

private:
    string _ID;
    string _username;
    string _password;
    string _name;
    string _birth;
    bool _sex;
    string _phone;
    // vector<Hotel*> _hotel;
    // vector<Tranport*> _tranport;
    // vector<Flight*> _flight;
public:
    void getInfo(json &j);

public:
    Account();
    Account(string nameUser, string password);
    Account(string nameUser, string password, string ID, string name, string birth, bool sex, string phone);
    ~Account();
    bool operator==(const Account &account);
    Account &operator=(const Account &account);
    string getName() { return _name; }
    string getID() { return _ID; }
    string getUsername() { return _username; }
    string getBirth() { return _birth; }
    bool getSex() { return _sex; }
    string getPhone() { return _phone; }

public:
    bool checkUsername(const Account &account);
    bool checkPassword(const Account &account);
    bool changeInfo(string password, string ID, string name, string birth, bool sex, string phone);
    bool changePassword(string password, string newpass, string checkpass);
};

Account *createAccount(string username, string password);
Account *createDetailAccount(string username, string password, string ID, string name, string birth, bool sex, string phone);


bool checkConditionUsername(string username);
bool checkConditionPassword(string password);
