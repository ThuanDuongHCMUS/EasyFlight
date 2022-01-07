#pragma once
#include "UserChecker.h"
#include "PasswordChecker.h"

class LinkedListAccount
{
private:
    AccountNode *_head;

public:
    LinkedListAccount();
    ~LinkedListAccount();

public:
    // Đọc file vào Chain
    void readFileJson(string address);
    void updateDatabase(string address);

public:
    bool findNodeWithName(AccountNode *accountNode, const Account &nameUser);
    bool findNodeWithPassword(AccountNode *accountNode, const Account &password);
    void addNode(AccountNode *accountNode);
    void delNode(AccountNode *accountNode);
    void getInfo(json &j);
    bool isExistUsername(Account *account);
    bool isExistAccount(Account *&account, char &cases);
    void printList();
};
