#include "editpassworddialog.h"
#include "ui_editpassworddialog.h"
#include <QMessageBox>

EditPasswordDialog::EditPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPasswordDialog)
{

    ui->setupUi(this);
}

EditPasswordDialog::~EditPasswordDialog()
{
    delete ui;
}

void EditPasswordDialog::on_exitButton_clicked()
{
    this->close();
    ui->checkNewPassword->clear();
    ui->newPassword->clear();
    ui->oldPassword->clear();
}


void EditPasswordDialog::on_okButton_clicked()
{
    string oldPassword = ui->oldPassword->text().toStdString();
    string newPassword = ui->newPassword->text().toStdString();
    string checkNewPassword = ui->checkNewPassword->text().toStdString();
    if (oldPassword.empty() || newPassword.empty() || checkNewPassword.empty()) {
        QMessageBox::warning(this, " ", "Không được để trống thông tin!");
        on_exitButton_clicked();
        return;
    }
    if (_user->changePassword(oldPassword, newPassword, checkNewPassword)) {
        QMessageBox::information(this, " ", "Đổi thông tin thành công!");
    }
    else {
        QMessageBox::warning(this, " ", "Không thể xác thực. Đổi thông tin thất bại!");
    }
    on_exitButton_clicked();
}

void EditPasswordDialog::setInfo(Account *user) {
    _user = user;
}

