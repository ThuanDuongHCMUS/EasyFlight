#include "Chain.h"

AccountNode::AccountNode()
{
    this->_key = nullptr;
    this->_next = nullptr;
}
AccountNode::AccountNode(Account *key)
{
    this->_key = key;
    this->_next = nullptr;
}
AccountNode::~AccountNode()
{
    if (_key) {
        _key = nullptr;
    }
    if (_next) {
        delete _next;
        _next = nullptr;
    }
    
}
void AccountNode::getInfo(json &j)
{
    this->_key->getInfo(j);
}
bool AccountNode::checkUsername(Account *account)
{
    return this->_key->checkUsername(*account);
}
bool AccountNode::checkPassword(Account *account)
{
    return this->_key->checkPassword(*account);
}
Chain::Chain()
{
}
Chain::~Chain()
{
}
