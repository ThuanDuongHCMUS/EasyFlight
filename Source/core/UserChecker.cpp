#include "UserChecker.h"
UserChecker::UserChecker() : Chain()
{
}
UserChecker::~UserChecker()
{
}
void UserChecker::setChecker(Chain *nextChain)
{
    this->_nextChain = nextChain;
}
bool UserChecker::check(AccountNode *accountNode, Account *account, char &cases)
{
    if (accountNode->checkUsername(account))
    {
        Chain *newChain = new PasswordChecker();
        this->setChecker(newChain);
        return this->_nextChain->check(accountNode, account, cases);
    }
    else
    {
        cases = 'u';
        return false;
    }
}