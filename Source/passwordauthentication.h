#ifndef PASSWORDAUTHENTICATION_H
#define PASSWORDAUTHENTICATION_H

#include <QDialog>
#include "core/Account.h"

namespace Ui {
class PasswordAuthentication;
}

class PasswordAuthentication : public QDialog
{
    Q_OBJECT
    string _ID, _name, _birth, _phone;
    bool _sex;
    Account* _user;

public:
    explicit PasswordAuthentication(QWidget *parent = nullptr);
    ~PasswordAuthentication();
    void setInfo(Account* user, string ID, string name, string birth, bool sex, string phone);
    bool isChanged;

private slots:
    void on_exitButton_clicked();

    void on_okButton_clicked();

private:
    Ui::PasswordAuthentication *ui;
};

#endif // PASSWORDAUTHENTICATION_H
