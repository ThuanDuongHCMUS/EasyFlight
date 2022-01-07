#ifndef EDITPASSWORDDIALOG_H
#define EDITPASSWORDDIALOG_H

#include <QDialog>
#include <core/Account.h>

namespace Ui {
class EditPasswordDialog;
}

class EditPasswordDialog : public QDialog
{
    Q_OBJECT
    Account* _user;

public:
    explicit EditPasswordDialog(QWidget *parent = nullptr);
    ~EditPasswordDialog();
    void setInfo(Account* user);

private slots:
    void on_exitButton_clicked();

    void on_okButton_clicked();

private:
    Ui::EditPasswordDialog *ui;
};

#endif // EDITPASSWORDDIALOG_H
