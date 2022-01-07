#include "passwordauthentication.h"
#include "ui_passwordauthentication.h"
#include <QMessageBox>

PasswordAuthentication::PasswordAuthentication(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordAuthentication)
{
    ui->setupUi(this);
    isChanged = false;
}

PasswordAuthentication::~PasswordAuthentication()
{
    delete ui;
}

void PasswordAuthentication::on_exitButton_clicked()
{
    ui->currentPassword->clear();
    this->close();
}


void PasswordAuthentication::on_okButton_clicked()
{
    string password = ui->currentPassword->text().toStdString();
    if (password.empty()) {
        QMessageBox::warning(this, " ", "Không được để trống!");
    }
    if (_user->changeInfo(password, _ID, _name, _birth, _sex, _phone)) {
        QMessageBox::information(this, " ", "Đổi thông tin thành công!");
        isChanged = true;
    }
    else {
        QMessageBox::warning(this, " ", "Không thể xác thực. Đổi thông tin thất bại!");
    }

    on_exitButton_clicked();
}

void PasswordAuthentication::setInfo(Account* user, string ID, string name, string birth, bool sex, string phone) {
    _user = user;
    _ID = ID;
    _name = name;
    _birth = birth;
    _sex = sex;
    _phone = phone;
}


