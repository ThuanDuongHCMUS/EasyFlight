#include "Account.h"

void Account::getInfo(json &j)
{
    json k;
    k["ID"] = this->_ID;
    k["Username"] = this->_username;
    k["Password"] = this->_password;
    k["Name"] = this->_name;
    k["Birth"] = this->_birth;
    k["Sex"] = this->_sex;
    k["Phone"] = this->_phone;

    j.push_back(k);
}
Account::Account()
{
}
Account::Account(string nameUser, string password)
{
    this->_username = nameUser;
    this->_password = password;
}
Account::Account(string nameUser, string password, string ID, string name, string birth, bool sex, string phone)
{
    this->_username = nameUser;
    this->_password = password;
    this->_ID = ID;
    this->_name = name;
    this->_birth = birth;
    this->_sex = sex;
    this->_phone = phone;
}
Account::~Account()
{
}
bool Account::operator==(const Account &account)
{
//    if (account._username != this->_username || account._password != this->_password)
//        return 0;
//    return 1;
    return (account._username == this->_username);
}
Account &Account::operator=(const Account &account)
{
    this->_username = account._username;
    this->_password = account._password;
    this->_ID = account._ID;
    this->_name = account._name;
    this->_birth = account._birth;
    this->_sex = account._sex;
    this->_phone = account._phone;
    return *this;
}
bool Account::checkUsername(const Account &account)
{
    return this->_username == account._username;
}
bool Account::checkPassword(const Account &account)
{
    return this->_password == account._password;
}

bool Account::changeInfo(string password, string ID, string name, string birth, bool sex, string phone)
{
    if (password != this->_password)
        return false;
    this->_ID = ID;
    this->_name = name;
    this->_birth = birth;
    this->_sex = sex;
    this->_phone = phone;
    return true;
}

bool Account::changePassword(string password, string newpass, string checkpass)
{
    if (password != this->_password)
        return false;
    if (checkConditionPassword(newpass) && newpass != this->_password)
    {
        if (newpass == checkpass)
        {
            this->_password = newpass;
            return true;
        }
    }
    return false;
}

Account *createAccount(string username, string password)
{
    if (checkConditionUsername(username) && checkConditionPassword(password))
        return new Account(username, password);
    return nullptr;
}

Account *createDetailAccount(string username, string password, string ID, string name, string birth, bool sex, string phone)
{
    if (checkConditionUsername(username) && checkConditionPassword(password))
        return new Account(username, password, ID, name, birth, sex, phone);
    return nullptr;
}

bool checkConditionUsername(string username)
{
    int n = username.length();
    int i = 0;
    while (i < n)
    {
        if (!((username[i] <= 'Z' && username[i] >= 'A') || (username[i] <= 'z' && username[i] >= 'a') || (username[i] <= '9' && username[i] >= '0')))
            return false;
        i++;
    }
    return true;
}
bool checkConditionPassword(string password)
{
    int n = password.length();
    int i = 0;
    while (i < n)
    {
        if (!((password[i] <= 'Z' && password[i] >= 'A') || (password[i] <= 'z' && password[i] >= 'a') || (password[i] <= '9' && password[i] >= '0')))
            return false;
        i++;
    }
    return true;
}


