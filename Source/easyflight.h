#ifndef EASYFLIGHT_H
#define EASYFLIGHT_H

#include <QWidget>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include "core/Login.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QFrame>
#include "editpassworddialog.h"
#include "passwordauthentication.h"
#include <QLayout>
#include "core/Facade/Facade.h"
#include <QHash>
#include <QSignalMapper>

QT_BEGIN_NAMESPACE
namespace Ui {
    class easyflight;
}
QT_END_NAMESPACE


class easyflight : public QWidget
{
    Q_OBJECT
    friend class EditPasswordDialog;
    friend class PasswordAuthentication;
private:
    Account* user;
    LinkedListAccount* list;
    QString path, info, flights, hotels, taxi, bus, grab, userdb;
    EditPasswordDialog* dialog;
    PasswordAuthentication* authN;
    Facade* facade;

    QFrame* flightFrame(vector<string> flightinfo, int index, string current);
    QFrame* hotelFrame(vector<string> info, int index, int amount);
    QFrame* transportFrame(vector<string> info, int index, string current);

    QFrame* flightFrameB(vector<string> info, int index);
    QFrame* hotelFrameB(vector<string> info, int index);
    QFrame* transportFrameB(vector<string> info, int index);

    QHash<QPushButton*, vector<string>> flightInfo;
    QHash<QPushButton*, vector<string>> hotelInfo;
    QHash<QPushButton*, vector<string>> transportInfo;
    QHash<QPushButton*, QHBoxLayout*> bookedMenu;
    QHash<QPushButton*, int> flightBid;
    QHash<QPushButton*, int> hotelBid;
    QHash<QPushButton*, int> transportBid;


    QPushButton* tempBtn;
    vector<int> choices;


public:
    easyflight(QWidget *parent = nullptr);
    ~easyflight();
    bool SignUp();


private slots:
    void on_logInButton_clicked();

    void on_logOutButton_clicked();

    void on_bookTicket_clicked();

    void on_signUpButton_clicked();

    void on_pushButton_doneSignUp_clicked();

    void on_pushButton_backSignUp_clicked();

    void on_profileButton_clicked();

    void on_manageButton_clicked();

    void on_bookHotel_clicked();

    void on_bookTransport_clicked();

    void on_pushButton_backProfile_clicked();

    void on_pushButton_backBookTicket_clicked();

    void on_pushButton_searchFlightBookTicket_clicked();

    void on_pushButton_backBookHotel_clicked();

    void on_pushButton_searchHotel_clicked();

    void on_pushButton_searchTransport_clicked();

    void on_pushButton_backBookTransport_clicked();

    void on_pushButton_backManageReserved_clicked();

    void on_pushButton_backFlightMenu_clicked();

    void on_pushButton_backHotelMenu_clicked();

    void on_pushButton_backTransportMenu_clicked();

    void on_pushButton_doneProfile_clicked();

    void on_pushButton_editPassword_clicked();

    void on_pushButton_backConfirmFlight_clicked();

    void on_pushButton_backConfirmHotel_clicked();

    void on_pushButton_backConfirmTransport_clicked();

    void on_pushButton_purchaseConfirmFlight_clicked();

    void on_pushButton_purchaseConfirmHotel_clicked();

    void on_pushButton_purchaseConfirmTransport_clicked();

public slots:
    void confirmFlight();
    void confirmHotel();
    void confirmTransport();
    void deleteFlightFrame();
    void deleteHotelFrame();
    void deleteTransFrame();

private:
    Ui::easyflight *ui;
};
#endif // EASYFLIGHT_H
