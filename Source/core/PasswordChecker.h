#pragma once
#include "Chain.h"
#include "UserChecker.h"

class PasswordChecker : public Chain
{
private:
    Chain *_nextChain;

public:
    static int _count;

public:
    PasswordChecker();
    ~PasswordChecker();

public:
    void setChecker(Chain *nextChain);
    bool check(AccountNode *accountNode, Account *account, char &cases);
};