#pragma once
#include "Chain.h"
#include "PasswordChecker.h"

class UserChecker : public Chain
{
private:
    Chain *_nextChain;

public:
    UserChecker();
    ~UserChecker();

public:
    void setChecker(Chain *nextChain);
    bool check(AccountNode *accountNode, Account *account, char &cases);
};
