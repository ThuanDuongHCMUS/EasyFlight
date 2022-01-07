#pragma once
#include "LIBLogin.h"

void inputPassword(string &password);
bool signUp(LinkedListAccount *linkedList);
Account *logIn(LinkedListAccount *linkedList);
bool logOut(Account **account);