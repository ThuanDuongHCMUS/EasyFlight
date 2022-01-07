#include "PasswordChecker.h"

int PasswordChecker::_count = 0;

PasswordChecker::PasswordChecker() : Chain()
{
    this->_nextChain = NULL;
}
PasswordChecker::~PasswordChecker()
{
    delete this->_nextChain;
    this->_nextChain = NULL;
}
void PasswordChecker::setChecker(Chain *nextChain)
{
    this->_nextChain = nextChain;
}
bool PasswordChecker::check(AccountNode *accountNode, Account *account, char &cases)
{
    if (accountNode->checkPassword(account))
    {
//        this->_count = 0;
        cases = 'a';
        return true;
    }
    else
    {
//        this->_count++;
//        if (this->_count == 3)
//        {
//            cases = 'l';
//            this->_count = 0;
//        }
//        else
            cases = 'p';
        return false;
        /*
        delete account;
        account = createAccount();
        Chain *newChain = new UserChecker();
        this->setChecker(newChain);

        return this->_nextChain->check(accountNode, account);
        */
    }
}
