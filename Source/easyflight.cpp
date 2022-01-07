#include "easyflight.h"
#include "ui_easyflight.h"

easyflight::easyflight(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::easyflight)
{
    ui->setupUi(this);
    authN = new PasswordAuthentication(this);
    authN->setWindowTitle("Xác nhận mật khẩu");
    dialog = new EditPasswordDialog(this);
    dialog->setWindowTitle("Đổi mật khẩu");

    ui->stackedWidget->setCurrentIndex(0);

    ui->dateEditSignUp->setDisplayFormat("dd/MM/yyyy");
    ui->dateEditProfile->setDisplayFormat("dd/MM/yyyy");
    ui->dateEditBookTicket->setDisplayFormat("dd/MM/yyyy");
    ui->dateEditBookTicket_return->setDisplayFormat("dd/MM/yyyy");
    ui->dateEditBookHotel_receive->setDisplayFormat("dd/MM/yyyy");
    ui->dateEditBookTransport->setDisplayFormat("dd/MM/yyyy");


    ui->dateEditSignUp->setDate(QDate::currentDate());
    ui->dateEditProfile->setDate(QDate::currentDate());
    ui->dateEditBookTicket->setDate(QDate::currentDate());
    ui->dateEditBookTicket_return->setDate(QDate::currentDate());
    ui->dateEditBookHotel_receive->setDate(QDate::currentDate());
    ui->dateEditBookTransport->setDate(QDate::currentDate());

    ui->timeEdit_bookTransport->setDisplayFormat("hh:mm");
    ui->timeEdit_bookTransport->setTime(QTime::currentTime());

    path = QDir::currentPath();
    info = path + "/database/info.json";
    flights = path + "/database/flights.json";
    hotels = path + "/database/hotels.json";
    taxi = path + "/database/taxi.json";
    grab = path + "/database/grab.json";
    bus = path + "/database/bus.json";

    userdb = path;

    list = new LinkedListAccount;
    list->readFileJson(info.toStdString());

    facade = new Facade;
    facade->readFileJsonFlight(flights.toStdString());
    facade->readFileJsonHotel(hotels.toStdString());
    facade->readFileJsonTransport(taxi.toStdString(), 0);
    facade->readFileJsonTransport(bus.toStdString(), 1);
    facade->readFileJsonTransport(grab.toStdString(), 2);
}

easyflight::~easyflight()
{
    if (user) {
        user = nullptr;
        facade->updateAvailableUserBooked(userdb.toStdString());
    }
    list->updateDatabase(info.toStdString());
    facade->updateAvailableFlight(flights.toStdString());
    facade->updateAvailableHotel(hotels.toStdString());
    facade->updateAvailableTransport(grab.toStdString(), bus.toStdString(), taxi.toStdString());
    delete list;
    delete facade;
    delete ui;
}

void easyflight::on_logInButton_clicked()
{
    string username = ui->lineEdit_username->text().toStdString();
    string password = ui->lineEdit_password->text().toStdString();
    user = new Account(username, password);
    char cases;
    if (!list->isExistAccount(user, cases))
    {
        if (cases == 'u')
            QMessageBox::warning(this, " ", "Tên đăng nhập không tồn tại!");
        else // if (cases == 'p')
            QMessageBox::warning(this, " ", "Mật khẩu không đúng!");
        delete user;
    }
    else {
        QMessageBox::information(this, " ", "Đăng nhập thành công");
        ui->stackedWidget->setCurrentIndex(1);
        ui->lineEdit_username->clear();
        ui->lineEdit_password->clear();
        QString name = QString::fromStdString(user->getName());
        if (name.size() == 0) name = "Ẩn danh";
        ui->nameDisplay->setText(name);
        ui->usernameDisplay->setText("Username: " + QString::fromStdString(username));

        userdb += "/database/" + QString::fromStdString(username) + ".json";

        facade->readFileJsonUserBooked(userdb.toStdString());
    }
}

void easyflight::on_logOutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    facade->updateAvailableUserBooked(userdb.toStdString());
    facade->delBooked();

    if (user) {
        user = nullptr;
    }

    userdb = path;
}

void easyflight::on_bookTicket_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void easyflight::on_signUpButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

bool easyflight::SignUp() {
    string username = ui->lineEdit_usernameSignUp->text().toStdString();
    string password = ui->lineEdit_passwordSignUp->text().toStdString();
//    wstring name = ui->lineEdit_signUpName->text().toStdWString();
    string name = ui->lineEdit_signUpName->text().toStdString();
    string birth = ui->dateEditSignUp->text().toStdString();
    birth = DateTime::ParseDate(birth);
    bool sex = (ui->sexEditSignUp->currentText() == "Nam") ? true : false;
    string ID = ui->lineEdit_IDSignUp->text().toStdString();
    string phone = ui->lineEdit_phoneSignUp->text().toStdString();
    if (username.empty() || password.empty() || name.empty() || ID.empty() || phone.empty()) {
        QMessageBox::warning(this, " ", "Không được để trống thông tin!");
        return false;
    }
    user = createDetailAccount(username, password, ID, name, birth, sex, phone);
    if (user == nullptr) {
        QMessageBox::warning(this, " ", "Tên đăng nhập hoặc mật khẩu nhập sai quy tắc!"); // Tao box quy tac trong man hinh dang ky
        return false;
    }
    if (list->isExistUsername(user)) {
        QMessageBox::warning(this, "Đăng ký lỗi", "Tên đăng nhập đã được sử dụng!");
        delete user;
        return false;
    }
    list->addNode(new AccountNode(user));
    QMessageBox::information(this, " ", "Đăng ký thành công!");
    return true;
}

void easyflight::on_pushButton_doneSignUp_clicked()
{
    if (SignUp()) {
        on_pushButton_backSignUp_clicked();
    }
}


void easyflight::on_pushButton_backSignUp_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_usernameSignUp->clear();
    ui->lineEdit_passwordSignUp->clear();
    ui->lineEdit_IDSignUp->clear();
    ui->sexEditSignUp->setCurrentIndex(0);
    ui->lineEdit_signUpName->clear();
    ui->lineEdit_phoneSignUp->clear();
    ui->dateEditSignUp->setDate(QDate::fromString("01/01/2000", "dd/MM/yyyy"));
}

void easyflight::on_profileButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->lineEdit_IDProfile->setPlaceholderText(QString::fromStdString(user->getID()));
    ui->lineEdit_nameProfile->setPlaceholderText(QString::fromStdString(user->getName()));
    ui->usernameProfile->setText(QString::fromStdString(user->getUsername()));
    ui->lineEdit_phoneProfile->setPlaceholderText(QString::fromStdString(user->getPhone()));
    ui->sexEditProfile->setCurrentIndex((user->getSex()) ? 0 : 1);
    ui->dateEditProfile->setDate(QDate::fromString(QString::fromStdString(DateTime::ToDate(user->getBirth())), "dd/MM/yyyy"));
}

void easyflight::on_pushButton_doneProfile_clicked()
{
    if (authN->isChanged) {
        authN->isChanged = false;
        on_pushButton_backProfile_clicked();
        ui->nameDisplay->setText(QString::fromStdString(user->getName()));
        return;
    }
    // dùng decode và encode thay cho việc sử dụng getter?
//    wstring name = ui->lineEdit_signUpName->text().toStdWString();
    string name = ui->lineEdit_nameProfile->text().toStdString();
    string birth = ui->dateEditProfile->text().toStdString();
    birth = DateTime::ParseDate(birth);
    bool sex = (ui->sexEditSignUp->currentText() == "Nam") ? true : false;
    string ID = ui->lineEdit_IDProfile->text().toStdString();
    string phone = ui->lineEdit_phoneProfile->text().toStdString();
    string password = "dummy password";

    if (name.empty()) name = user->getName();
    if (ID.empty()) ID = user->getID();
    if (phone.empty()) phone = user->getPhone();
    // pop up dialog to enter the password for the authentication
    authN->show();
    authN->setInfo(user, ID, name, birth, sex, phone);
}

void easyflight::on_manageButton_clicked()
{

    ui->stackedWidget->setCurrentIndex(8);

    QFrame* mainframe = new QFrame(ui->scrollArea_flight);
    QFrame* frame = new QFrame(mainframe);
    mainframe->setContentsMargins(0, 0, 0, 0);
    frame->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout* layout = new QVBoxLayout(frame);
    for (int i = 0; i < facade->_bkdTck.size(); ++i) {

        QFrame* newframe = flightFrameB(facade->_bkdTck[i]->info(), i);
        layout->addWidget(newframe, Qt::AlignHCenter);
    }

    QVBoxLayout* layout2 = new QVBoxLayout(mainframe);
    layout2->addWidget(frame, 0, Qt::AlignTop);
    ui->scrollArea_flight->setWidget(mainframe);
    //----------------------------------------------------------------

    QFrame* mainframe1 = new QFrame(ui->scrollArea_hotel);
    QFrame* frame1 = new QFrame(mainframe1);
    mainframe1->setContentsMargins(0, 0, 0, 0);
    frame1->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout* layout1 = new QVBoxLayout(frame1);
    for (int i = 0; i < facade->_bkdHtl.size(); ++i) {

        QFrame* newframe1 = hotelFrameB(facade->_bkdHtl[i]->info(), i);
        layout1->addWidget(newframe1, Qt::AlignHCenter);
    }

    QVBoxLayout* layout21 = new QVBoxLayout(mainframe1);
    layout21->addWidget(frame1, 0, Qt::AlignTop);
    ui->scrollArea_hotel->setWidget(mainframe1);

    //-----------------------------------------------------------------

    QFrame* mainframe2 = new QFrame(ui->scrollArea_transport);
    QFrame* frame2 = new QFrame(mainframe2);
    mainframe2->setContentsMargins(0, 0, 0, 0);
    frame2->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout* layout22 = new QVBoxLayout(frame2);
    for (int i = 0; i < facade->_bkdTrs.size(); ++i) {

        QFrame* newframe2 = transportFrameB(facade->_bkdTrs[i]->info(), i);
        layout22->addWidget(newframe2, Qt::AlignHCenter);
    }

    QVBoxLayout* layout222 = new QVBoxLayout(mainframe2);
    layout222->addWidget(frame2, 0, Qt::AlignTop);
    ui->scrollArea_transport->setWidget(mainframe2);


}

void easyflight::on_bookHotel_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void easyflight::on_bookTransport_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void easyflight::on_pushButton_backProfile_clicked()
{
    ui->lineEdit_IDProfile->clear();
    ui->lineEdit_nameProfile->clear();
    ui->lineEdit_phoneProfile->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

void easyflight::on_pushButton_backBookTicket_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->comboBox_arrivalAirport->setCurrentIndex(0);
    ui->comboBox_departureAirport->setCurrentIndex(0);
    ui->dateEditBookTicket->setDate(QDate::currentDate());
    ui->dateEditBookTicket_return->setDate(QDate::currentDate());
    ui->checkBox_bookTicket->setCheckState(Qt::Unchecked);
}

// truyen vao 1 flight
QFrame* easyflight::flightFrame(vector<string> flightinfo, int index, string current) {
    QFrame* frame = new QFrame();

    frame->setContentsMargins(0, 0, 0, 0);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    QHBoxLayout* hlayout = new QHBoxLayout(frame);
    QFrame* frameLeft = new QFrame(frame);
    QFrame* frameRight = new QFrame(frame);

    QFrame* frameMid = new QFrame(frame);

    frameLeft->setFrameShadow(QFrame::Raised);
    frameLeft->setFrameShape(QFrame::StyledPanel);

    frameRight->setFrameShadow(QFrame::Raised);
    frameRight->setFrameShape(QFrame::StyledPanel);

    frameMid->setFrameShadow(QFrame::Raised);
    frameMid->setFrameShape(QFrame::StyledPanel);

    QVBoxLayout* vleft = new QVBoxLayout(frameLeft);
    QLabel* departureAirport = new QLabel(frameLeft);

    QVBoxLayout* vright = new QVBoxLayout(frameRight);
    QLabel* arrivalAirport = new QLabel(frameRight);

    QLabel* departureTime = new QLabel(frameLeft);
    departureTime->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));
    QLabel* arrivalTime = new QLabel(frameRight);
    arrivalTime->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));
    QLabel* departureDate = new QLabel(frameLeft);
    departureDate->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));
    QLabel* arrivalDate = new QLabel(frameRight);
    arrivalDate->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    vleft->addWidget(departureAirport, 0, Qt::AlignHCenter);
    vleft->addWidget(departureDate, 0, Qt::AlignHCenter);
    vleft->addWidget(departureTime, 0, Qt::AlignHCenter);


    hlayout->addWidget(frameLeft, Qt::AlignHCenter);

    QVBoxLayout* mlayout = new QVBoxLayout(frameMid);

    QLabel* fare = new QLabel(frameMid);
    fare->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    mlayout->addWidget(fare);

    QLabel* arrow = new QLabel(frameMid);
    arrow->setMinimumSize(QSize(50, 50));
    arrow->setMaximumSize(QSize(50, 50));
    arrow->setPixmap(QPixmap(QString::fromUtf8("../img/right-arrow.png")));
    arrow->setScaledContents(true);

    mlayout->addWidget(arrow);

    hlayout->addWidget(frameMid, 0, Qt::AlignHCenter);

    vright->addWidget(arrivalAirport, 0, Qt::AlignHCenter);
    vright->addWidget(arrivalDate, 0, Qt::AlignHCenter);
    vright->addWidget(arrivalTime, 0, Qt::AlignHCenter);

    hlayout->addWidget(frameRight, 0, Qt::AlignHCenter);

    QPushButton* nextBtn = new QPushButton(frame);
    nextBtn->setMinimumSize(QSize(50, 50));
    nextBtn->setMaximumSize(QSize(50, 50));
    QIcon icon;
    icon.addFile(QString::fromUtf8("../img/feather/arrow-right-circle.svg"), QSize(), QIcon::Normal, QIcon::Off);
    nextBtn->setIcon(icon);
    nextBtn->setIconSize(QSize(30, 30));

    hlayout->addWidget(nextBtn, Qt::AlignRight);

    departureAirport->setText(QString::fromStdString(flightinfo[1]));
    arrivalAirport->setText(QString::fromStdString(flightinfo[0]));

    fare->setText(QString::fromStdString(flightinfo[4]) + "kVND");

    string depT = DateTime::ToTime(flightinfo[3].substr(8));
    string arrT = DateTime::ToTime(flightinfo[2].substr(8));
    string depD = DateTime::ToDate(flightinfo[3].substr(0, 8));
    string arrD = DateTime::ToDate(flightinfo[2].substr(0, 8));

    departureTime->setText(QString::fromStdString(depT));
    arrivalTime->setText(QString::fromStdString(arrT));
    departureDate->setText(QString::fromStdString(depD));
    arrivalDate->setText(QString::fromStdString(arrD));

    flightinfo.push_back(to_string(index)); // 5
    flightinfo.push_back(current);
    flightInfo.insert(nextBtn, flightinfo);
    QObject::connect(nextBtn, SIGNAL(clicked()), this, SLOT(confirmFlight()));

    return frame;
}

void easyflight::on_pushButton_searchFlightBookTicket_clicked()
{
    if (ui->comboBox_arrivalAirport->currentIndex() == 0 || ui->comboBox_departureAirport->currentIndex() == 0) {
        QMessageBox::warning(this, " ", "Không được để trống địa điểm!");
        return;
    }
    string departure = ui->comboBox_departureAirport->currentText().left(3).toStdString();
    string arrival = ui->comboBox_arrivalAirport->currentText().left(3).toStdString().substr(0, 3);
    if (arrival == departure) {
        QMessageBox::warning(this, " ", "Vui lòng chọn nơi đi khác nơi đến!");
        return;
    }
    string date = DateTime::ParseDate(ui->dateEditBookTicket->text().toStdString()) + "0000";
//    Date d1(date);
//    string returnDate = DateTime::ParseDate(ui->dateEditBookTicket_return->text().toStdString());
//    bool checkReturn = ui->checkBox_bookTicket->checkState(); // chon chuyen di truoc chon chuyen ve sau

    string current = DateTime::ParseDate(QDate::currentDate().toString("dd/MM/yyyy").toStdString())
            + DateTime::ParseTime(QTime::currentTime().toString("hh:mm").toStdString());

//    Date curd(current);

//    if (curd == d1) date = current;

    vector<Flight*> filtered = facade->availableFlight(departure, arrival, date, current);

    // UI
    QFrame* mainframe = new QFrame(ui->scrollArea_FlightMenu);
    QFrame* frame = new QFrame(mainframe);
    mainframe->setContentsMargins(0, 0, 0, 0);
    frame->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout* layout = new QVBoxLayout(frame);

    for (int i = 0; i < filtered.size(); ++i) {

        QFrame* newframe = flightFrame(filtered[i]->info(), i, current);
        layout->addWidget(newframe, Qt::AlignHCenter);

    }

    QVBoxLayout* layout2 = new QVBoxLayout(mainframe);
    layout2->addWidget(frame, 0, Qt::AlignTop);
    ui->scrollArea_FlightMenu->setWidget(mainframe);
    ui->stackedWidget->setCurrentIndex(9);
}

void easyflight::on_pushButton_backBookHotel_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->comboBox_arrivalBookHotel->setCurrentIndex(0);
    ui->dateEditBookHotel_receive->setDate(QDate::currentDate());
    ui->spinBox_nRooms->setValue(0);
}

// truyen vao 1 hotel
QFrame* easyflight::hotelFrame(vector<string> info, int index, int amount) {
    QFrame* hotelmainframe = new QFrame();
    hotelmainframe->setContentsMargins(0, 0, 0, 0);
    hotelmainframe->setMinimumSize(QSize(300, 120));
    hotelmainframe->setMaximumSize(QSize(500, 120));
    hotelmainframe->setFrameShape(QFrame::StyledPanel);
    hotelmainframe->setFrameShadow(QFrame::Raised);

    QHBoxLayout *hlayout = new QHBoxLayout(hotelmainframe);
    hlayout->setContentsMargins(0, 0, 0, 0);

    QLabel* hotelimg = new QLabel(hotelmainframe);
    hotelimg->setMinimumSize(QSize(60, 100));
    hotelimg->setMaximumSize(QSize(60, 100));
    hotelimg->setPixmap(QPixmap(QString::fromStdString(info[4])));
//    hotelimg->setPixmap(QPixmap(QString::fromStdString("../img/testhotel.png")));
    hotelimg->setScaledContents(true);

    hlayout->addWidget(hotelimg);

    QFrame* addressFrame = new QFrame(hotelmainframe);
    addressFrame->setMinimumSize(QSize(200, 120));
    addressFrame->setMaximumSize(QSize(200, 120));
    addressFrame->setFrameShape(QFrame::StyledPanel);
    addressFrame->setFrameShadow(QFrame::Raised);

    QVBoxLayout* vlayout = new QVBoxLayout(addressFrame);

    QLabel* hotelNameLabel = new QLabel(addressFrame);

    vlayout->addWidget(hotelNameLabel, 0, Qt::AlignHCenter);

    QLabel* hotelRoomleftLabel = new QLabel(addressFrame);
    hotelRoomleftLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    vlayout->addWidget(hotelRoomleftLabel, 0, Qt::AlignHCenter);

    QLabel* hotelCostLabel = new QLabel(addressFrame);
    hotelCostLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    vlayout->addWidget(hotelCostLabel, 0, Qt::AlignHCenter);

    hlayout->addWidget(addressFrame, 0, Qt::AlignLeft);

    QPushButton* hotelPushButton = new QPushButton(hotelmainframe);
    hotelPushButton->setObjectName(QString::fromUtf8("hotelPushButton"));
    hotelPushButton->setMinimumSize(QSize(50, 50));
    hotelPushButton->setMaximumSize(QSize(50, 50));
    QIcon icon;
    icon.addFile(QString::fromUtf8("../img/feather/arrow-right-circle.svg"), QSize(), QIcon::Normal, QIcon::Off);
    hotelPushButton->setIcon(icon);
    hotelPushButton->setIconSize(QSize(30, 30));

    hlayout->addWidget(hotelPushButton);

    hotelNameLabel->setText(QString::fromStdString(info[0]));
    hotelRoomleftLabel->setText("Còn: " + QString::fromStdString(info[2]) + " phòng");
    hotelCostLabel->setText("Giá: " + QString::fromStdString(info[3]) + " kVND");

    QObject::connect(hotelPushButton, SIGNAL(clicked()), this, SLOT(confirmHotel()));

    info[2] = to_string(stoi(info[2]) * amount);
    info.push_back(to_string(amount)); // 5
    info.push_back(to_string(index)); // 6
    hotelInfo.insert(hotelPushButton, info);

    return hotelmainframe;
}

QString unaccent(const QString s)
{
    QString output(s.normalized(QString::NormalizationForm_KD));
    output = output.replace("Đ", "D");
    output = output.replace(QRegExp("[^a-zA-Z\\s]"), "");
    return output;
}

void easyflight::on_pushButton_searchHotel_clicked()
{
    string location = unaccent(ui->comboBox_arrivalBookHotel->currentText()).toStdString();
    if (location.empty()) {
        QMessageBox::warning(this, " ", "Không được để trống địa điểm!");
        return;
    }

    int amount = ui->spinBox_nRooms->value();
    if (amount == 0) {
        QMessageBox::information(this, " ", "Bạn đang không đặt phòng nào!");
        return;
    }
    vector<Hotel*> filtered = facade->availableHotel(location, amount);

    // UI
    ui->stackedWidget->setCurrentIndex(10);
    QFrame* mainframe = new QFrame(ui->scrollArea_HotelMenu);
    QFrame* frame = new QFrame(mainframe);
    mainframe->setContentsMargins(0, 0, 0, 0);
    frame->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout* layout = new QVBoxLayout(frame);
    for (int i = 0; i < filtered.size(); ++i) {
        QFrame* newframe = hotelFrame(filtered[i]->info(), i, amount);
        layout->addWidget(newframe, Qt::AlignHCenter);
    }

    QVBoxLayout* layout2 = new QVBoxLayout(mainframe);
    layout2->addWidget(frame, 0, Qt::AlignTop);
    ui->scrollArea_HotelMenu->setWidget(mainframe);
}

QFrame* easyflight::transportFrame(vector<string> info, int index, string current) {
    QFrame* modelTransportFrame = new QFrame();
    modelTransportFrame->setMinimumSize(QSize(300, 100));
    modelTransportFrame->setMaximumSize(QSize(500, 100));
    modelTransportFrame->setFrameShape(QFrame::StyledPanel);
    modelTransportFrame->setFrameShadow(QFrame::Raised);
    QHBoxLayout* hlayout = new QHBoxLayout(modelTransportFrame);

    QLabel* transportimg = new QLabel(modelTransportFrame);
    transportimg->setMinimumSize(QSize(50, 50));
    transportimg->setMaximumSize(QSize(50, 50));

    string path = "../img/" + info[0] + ".png";
    transportimg->setPixmap(QPixmap(QString::fromStdString(path)));
    transportimg->setScaledContents(true);

    hlayout->addWidget(transportimg);

    QFrame* infoTransportFrame = new QFrame(modelTransportFrame);
    infoTransportFrame->setMinimumSize(QSize(200, 0));
    infoTransportFrame->setMaximumSize(QSize(200, 100));
    infoTransportFrame->setFrameShape(QFrame::StyledPanel);
    infoTransportFrame->setFrameShadow(QFrame::Raised);

    QVBoxLayout* vlayout = new QVBoxLayout(infoTransportFrame);

    QLabel* transportNameLabel = new QLabel(infoTransportFrame);

    vlayout->addWidget(transportNameLabel, 0, Qt::AlignHCenter);

    QLabel* transportRangeLabel = new QLabel(infoTransportFrame);
    transportRangeLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    vlayout->addWidget(transportRangeLabel, 0, Qt::AlignHCenter);

    QLabel* transportFare = new QLabel(infoTransportFrame);
    transportFare->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    vlayout->addWidget(transportFare, 0, Qt::AlignHCenter);


    hlayout->addWidget(infoTransportFrame);

    QPushButton* btn = new QPushButton(modelTransportFrame);
    btn->setMinimumSize(QSize(50, 50));
    btn->setMaximumSize(QSize(50, 50));
    QIcon icon;
    icon.addFile(QString::fromUtf8("../img/feather/arrow-right-circle.svg"), QSize(), QIcon::Normal, QIcon::Off);
    btn->setIcon(icon);
    btn->setIconSize(QSize(30, 30));

    hlayout->addWidget(btn, 0, Qt::AlignRight);
    transportFare->setText("Giá tiền: " + QString::fromStdString(info[1]) + "kVND");
    transportNameLabel->setText("Biển số xe: " + QString::fromStdString(info[2]));

    QHash<int, QString> ranges;
    ranges.insert(5, "5km");
    ranges.insert(10, "10km");
    ranges.insert(25, "25km");
    ranges.insert(50, "50km");
    ranges.insert(51, "Trên 50km");

    transportRangeLabel->setText("Phạm vi: " + ranges[stoi(info[3])]);

    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(confirmTransport()));

    info.push_back(to_string(index)); // 5
    info.push_back(current);
    transportInfo.insert(btn, info);

    return modelTransportFrame;
}

void easyflight::on_pushButton_searchTransport_clicked()
{
    if (ui->comboBox_range->currentIndex() == 0 || ui->comboBox_departureAirportTransport->currentIndex() == 0) {
        QMessageBox::warning(this, " ", "Không được để trống thông tin!");
        return;
    }
    string location = unaccent(ui->comboBox_departureAirportTransport->currentText()).toStdString();
    string time = DateTime::ParseTime(ui->timeEdit_bookTransport->text().toStdString());

    int ranges[] = {5, 10, 25, 50, 51};

    int range = ranges[ui->comboBox_range->currentIndex() - 1];

    vector<Transport*> filtered = facade->availableTransport(time, location, range);
    // UI
    ui->stackedWidget->setCurrentIndex(11);
    QFrame* mainframe = new QFrame(ui->scrollArea_TransportMenu);
    QFrame* frame = new QFrame(mainframe);
    mainframe->setContentsMargins(0, 0, 0, 0);
    frame->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout* layout = new QVBoxLayout(frame);
    for (int i = 0; i < filtered.size(); ++i) {
        QFrame* newframe = transportFrame(filtered[i]->info(), i, time);
        layout->addWidget(newframe, Qt::AlignHCenter);
    }

    QVBoxLayout* layout2 = new QVBoxLayout(mainframe);
    layout2->addWidget(frame, 0, Qt::AlignTop);
    ui->scrollArea_TransportMenu->setWidget(mainframe);
}

void easyflight::on_pushButton_backBookTransport_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->comboBox_departureAirportTransport->setCurrentIndex(0);
    ui->comboBox_range->setCurrentIndex(0);
    ui->dateEditBookTransport->setDate(QDate::currentDate());
    ui->timeEdit_bookTransport->setTime(QTime::currentTime());
}

void easyflight::on_pushButton_backManageReserved_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void easyflight::on_pushButton_backFlightMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void easyflight::on_pushButton_backHotelMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void easyflight::on_pushButton_backTransportMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void easyflight::on_pushButton_editPassword_clicked()
{
    dialog->show();
    dialog->setInfo(user);
}

void easyflight::confirmFlight() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    vector<string> info = flightInfo[buttonSender];
    tempBtn = buttonSender;

    ui->stackedWidget->setCurrentIndex(12);

    ui->departureAirportConfirm->setText(QString::fromStdString(info[1]));
    ui->arrivalAirportConfirm->setText(QString::fromStdString(info[0]));

    string depT = DateTime::ToTime(info[3].substr(8));
    string arrT = DateTime::ToTime(info[2].substr(8));
    string depD = DateTime::ToDate(info[3].substr(0, 8));
    string arrD = DateTime::ToDate(info[2].substr(0, 8));

    ui->departureTimeConfirm->setText(QString::fromStdString(depT));
    ui->arrivalTimeConfirm->setText(QString::fromStdString(arrT));
    ui->departureDateConfirm->setText(QString::fromStdString(depD));
    ui->arrivalDateConfirm->setText(QString::fromStdString(arrD));

    ui->fareConfirmFlight->setText(QString::fromStdString(info[4]) + "kVND");

    ui->nameConfirmFlight->setText(QString::fromStdString(user->getName()));
    ui->phoneConfirmFlight->setText(QString::fromStdString(user->getPhone()));
    ui->IDConfirmFlight->setText(QString::fromStdString(user->getID()));
    ui->sexConfirmFlight->setText(user->getSex() ? QString("Nam") : QString("Nữ"));
    ui->birthConfirmFlight->setText(QString::fromStdString(DateTime::ToDate(user->getBirth())));

    choices.clear();
    choices.push_back(stoi(info[5]));
}

void easyflight::on_pushButton_backConfirmFlight_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void easyflight::confirmHotel() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    vector<string> info = hotelInfo[buttonSender];
    tempBtn = buttonSender;

    ui->stackedWidget->setCurrentIndex(13);

    ui->nameConfirmHotel->setText(QString::fromStdString(user->getName()));
    ui->phoneConfirmHotel->setText(QString::fromStdString(user->getPhone()));
    ui->IDConfirmHotel->setText(QString::fromStdString(user->getID()));
    ui->sexConfirmHotel->setText(user->getSex() ? QString("Nam") : QString("Nữ"));
    ui->birthConfirmHotel->setText(QString::fromStdString(DateTime::ToDate(user->getBirth())));

    ui->nameConfirmHotel_2->setText(QString::fromStdString(info[0]));
    ui->locationConfirmHotel->setText(ui->comboBox_arrivalBookHotel->currentText());
    ui->nRoomConfirm->setText("Số phòng: " + QString::fromStdString(info[5]));
    ui->costConfirm->setText("Tổng tiền: " + QString::fromStdString(to_string(stoi(info[3]) * stoi(info[5]))) + "kVND");

    choices.clear();
    choices.push_back(stoi(info[6]));
}


void easyflight::on_pushButton_backConfirmHotel_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}


void easyflight::on_pushButton_backConfirmTransport_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}


void easyflight::confirmTransport() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    vector<string> info = transportInfo[buttonSender];
    tempBtn = buttonSender;

    ui->stackedWidget->setCurrentIndex(7);

    ui->nameConfirmTransport->setText(QString::fromStdString(user->getName()));
    ui->phoneConfirmTransport->setText(QString::fromStdString(user->getPhone()));
    ui->IDConfirmTransport->setText(QString::fromStdString(user->getID()));
    ui->sexConfirmTransport->setText(user->getSex() ? QString("Nam") : QString("Nữ"));
    ui->birthConfirmTransport->setText(QString::fromStdString(DateTime::ToDate(user->getBirth())));

    ui->CostTransportConfirm->setText("Giá tiền: " + QString::fromStdString(info[1]) + "kVND");
    ui->IDTransportConfirm->setText("Biển số xe: " + QString::fromStdString(info[2]));

    QHash<int, QString> ranges;
    ranges.insert(5, "5km");
    ranges.insert(10, "10km");
    ranges.insert(25, "25km");
    ranges.insert(50, "50km");
    ranges.insert(51, "Trên 50km");

    ui->rangeTransportConfirm->setText("Phạm vi: " + ranges[stoi(info[3])]);

    choices.clear();
    choices.push_back(stoi(info[5]));
}

void easyflight::on_pushButton_purchaseConfirmFlight_clicked()
{
    vector<string> info = flightInfo[tempBtn];

    vector<Ticket*> bookedTickets = facade->bookTicket(info[1], info[0], info[3].substr(0, 8) + "0000", info[3].substr(0, 8) + "0000", info.back(), choices, false);

    if (!bookedTickets.empty()) {
        QMessageBox::information(this, " ", "Đặt vé thành công!");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {
        QMessageBox::information(this, " ", "Đặt vé thất bại!");
        ui->stackedWidget->setCurrentIndex(10);
    }
}


QFrame* easyflight::flightFrameB(vector<string> info, int index) {
    QFrame* modelFrameFlightB = new QFrame();
    modelFrameFlightB->setFrameShape(QFrame::StyledPanel);
    modelFrameFlightB->setFrameShadow(QFrame::Raised);

    QHBoxLayout* horizontalLayout_30 = new QHBoxLayout(modelFrameFlightB);

    QFrame* frame_25 = new QFrame(modelFrameFlightB);
    frame_25->setFrameShape(QFrame::StyledPanel);
    frame_25->setFrameShadow(QFrame::Raised);

    QVBoxLayout* verticalLayout_55 = new QVBoxLayout(frame_25);

    QLabel* departureAirportConfirmB = new QLabel(frame_25);

    verticalLayout_55->addWidget(departureAirportConfirmB, 0, Qt::AlignHCenter);

    QLabel* departureDateConfirmB = new QLabel(frame_25);
    departureDateConfirmB->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    verticalLayout_55->addWidget(departureDateConfirmB, 0, Qt::AlignHCenter);

    QLabel* departureTimeConfirmB = new QLabel(frame_25);
    departureTimeConfirmB->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    verticalLayout_55->addWidget(departureTimeConfirmB, 0, Qt::AlignHCenter);


    horizontalLayout_30->addWidget(frame_25);

    QFrame* frame_26 = new QFrame(modelFrameFlightB);
    frame_26->setObjectName(QString::fromUtf8("frame_26"));
    frame_26->setFrameShape(QFrame::StyledPanel);
    frame_26->setFrameShadow(QFrame::Raised);

    QVBoxLayout* verticalLayout_56 = new QVBoxLayout(frame_26);
    QLabel* fareConfirmFlightB = new QLabel(frame_26);
    fareConfirmFlightB->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    verticalLayout_56->addWidget(fareConfirmFlightB, 0, Qt::AlignHCenter);

    QLabel* label_29 = new QLabel(frame_26);
    label_29->setMinimumSize(QSize(50, 50));
    label_29->setMaximumSize(QSize(50, 50));
    label_29->setPixmap(QPixmap(QString::fromUtf8("../img/right-arrow.png")));
    label_29->setScaledContents(true);

    verticalLayout_56->addWidget(label_29, 0, Qt::AlignHCenter);


    horizontalLayout_30->addWidget(frame_26);

    QFrame* frame_27 = new QFrame(modelFrameFlightB);
    frame_27->setFrameShape(QFrame::StyledPanel);
    frame_27->setFrameShadow(QFrame::Raised);

    QVBoxLayout* verticalLayout_57 = new QVBoxLayout(frame_27);
    QLabel* arrivalAirportConfirmB = new QLabel(frame_27);
    arrivalAirportConfirmB->setObjectName(QString::fromUtf8("arrivalAirportConfirm_2"));

    verticalLayout_57->addWidget(arrivalAirportConfirmB, 0, Qt::AlignHCenter);

    QLabel* arrivalDateConfirmB = new QLabel(frame_27);
    arrivalDateConfirmB->setObjectName(QString::fromUtf8("arrivalDateConfirm_2"));
    arrivalDateConfirmB->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    verticalLayout_57->addWidget(arrivalDateConfirmB, 0, Qt::AlignHCenter);

    QLabel* arrivalTimeConfirmB = new QLabel(frame_27);
    arrivalTimeConfirmB->setObjectName(QString::fromUtf8("arrivalTimeConfirm_2"));
    arrivalTimeConfirmB->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    verticalLayout_57->addWidget(arrivalTimeConfirmB, 0, Qt::AlignHCenter);


    horizontalLayout_30->addWidget(frame_27);

    QPushButton* btn = new QPushButton(modelFrameFlightB);
    btn->setObjectName(QString::fromUtf8("pushButton_3"));
    btn->setMinimumSize(QSize(30, 50));
    btn->setMaximumSize(QSize(30, 50));
    QIcon icon11;
    icon11.addFile(QString::fromUtf8("../img/feather/trash.svg"), QSize(), QIcon::Normal, QIcon::Off);
    btn->setIcon(icon11);
    btn->setIconSize(QSize(20, 50));

    horizontalLayout_30->addWidget(btn);


    departureAirportConfirmB->setText(QString::fromStdString(info[1]));
    arrivalAirportConfirmB->setText(QString::fromStdString(info[0]));

    fareConfirmFlightB->setText(QString::fromStdString(info[4]) + "kVND");

    string depT = DateTime::ToTime(info[3].substr(8, 4));
    string arrT = DateTime::ToTime(info[2].substr(8, 4));
    string depD = DateTime::ToDate(info[3].substr(0, 8));
    string arrD = DateTime::ToDate(info[2].substr(0, 8));

    departureTimeConfirmB->setText(QString::fromStdString(depT));
    arrivalTimeConfirmB->setText(QString::fromStdString(arrT));
    departureDateConfirmB->setText(QString::fromStdString(depD));
    arrivalDateConfirmB->setText(QString::fromStdString(arrD));

    flightBid.insert(btn, index);
    bookedMenu.insert(btn, horizontalLayout_30);
    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(deleteFlightFrame()));

    return modelFrameFlightB;
}

void easyflight::deleteFlightFrame() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    int index = flightBid[buttonSender];
    QHBoxLayout* layout = bookedMenu[buttonSender];
    while (layout->count() != 0) {
        QLayoutItem* item = layout->takeAt(0);
        delete item->widget();
    }
    facade->cancelTck(index);
}

QFrame* easyflight::hotelFrameB(vector<string> info, int index) {
    QFrame* modelFrameHotelB = new QFrame();

    modelFrameHotelB->setContentsMargins(0, 0, 0, 0);
    modelFrameHotelB->setFrameShape(QFrame::StyledPanel);
    modelFrameHotelB->setFrameShadow(QFrame::Raised);

    QHBoxLayout* hlayout = new QHBoxLayout(modelFrameHotelB);

    QFrame* frame_31 = new QFrame(modelFrameHotelB);
    frame_31->setFrameShape(QFrame::StyledPanel);
    frame_31->setFrameShadow(QFrame::Raised);

    QVBoxLayout* vlayout1 = new QVBoxLayout(frame_31);
    QLabel* nameConfirmHotel_3 = new QLabel(frame_31);

    vlayout1->addWidget(nameConfirmHotel_3, 0, Qt::AlignHCenter);

    QLabel* nRoomConfirm_2 = new QLabel(frame_31);
    nRoomConfirm_2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    vlayout1->addWidget(nRoomConfirm_2, 0, Qt::AlignHCenter);


    hlayout->addWidget(frame_31);

    QFrame* frame_30 = new QFrame(modelFrameHotelB);
    frame_30->setFrameShape(QFrame::StyledPanel);
    frame_30->setFrameShadow(QFrame::Raised);

    QVBoxLayout* vlayout2 = new QVBoxLayout(frame_30);

    QLabel* locationConfirmHotel_2 = new QLabel(frame_30);

    vlayout2->addWidget(locationConfirmHotel_2, 0, Qt::AlignHCenter);

    QLabel* costConfirm_2 = new QLabel(frame_30);
    costConfirm_2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    vlayout2->addWidget(costConfirm_2, 0, Qt::AlignHCenter);


    hlayout->addWidget(frame_30);

    QPushButton* btn = new QPushButton(modelFrameHotelB);
    btn->setMinimumSize(QSize(30, 50));
    btn->setMaximumSize(QSize(30, 50));
    QIcon icon11;
    icon11.addFile(QString::fromUtf8("../img/feather/trash.svg"), QSize(), QIcon::Normal, QIcon::Off);
    btn->setIcon(icon11);
    btn->setIconSize(QSize(20, 50));

    hlayout->addWidget(btn);
    hotelBid.insert(btn, index);
    bookedMenu.insert(btn, hlayout);
    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(deleteHotelFrame()));

    nameConfirmHotel_3->setText(QString::fromStdString(info[0]));
    nRoomConfirm_2->setText("Số phòng:      ");
    costConfirm_2->setText("Giá:       ");
    locationConfirmHotel_2->setText(QString::fromStdString(info[1]));

    return modelFrameHotelB;
}

void easyflight::deleteHotelFrame() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    int index = hotelBid[buttonSender];
    QHBoxLayout* layout = bookedMenu[buttonSender];
    while (layout->count() != 0) {
        QLayoutItem* item = layout->takeAt(0);
        delete item->widget();
    }
    facade->cancelHtl(index);
}

void easyflight::on_pushButton_purchaseConfirmHotel_clicked()
{
    vector<string> info = hotelInfo[tempBtn];
    vector<Hotel*> booked = facade->bookHotel(info[1], choices[0], stoi(info[5]));
    if (!booked.empty()) {
        QMessageBox::information(this, " ", "Đặt phòng thành công!");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {
        QMessageBox::information(this, " ", "Đặt phòng thất bại!");
        ui->stackedWidget->setCurrentIndex(11);
    }
}

QFrame* easyflight::transportFrameB(vector<string> info, int index) {
    QFrame* modelFrameTrsB = new QFrame();
    modelFrameTrsB->setFrameShape(QFrame::StyledPanel);
    modelFrameTrsB->setFrameShadow(QFrame::Raised);

    QHBoxLayout *horizontalLayout_33 = new QHBoxLayout(modelFrameTrsB);


    QLabel* transportimg = new QLabel(modelFrameTrsB);
    transportimg->setMinimumSize(QSize(50, 50));
    transportimg->setMaximumSize(QSize(50, 50));

    string path = "../img/" + info[0] + ".png";
    transportimg->setPixmap(QPixmap(QString::fromStdString(path)));
    transportimg->setScaledContents(true);

    horizontalLayout_33->addWidget(transportimg);

    QFrame* frame_29 = new QFrame(modelFrameTrsB);
    frame_29->setFrameShape(QFrame::StyledPanel);
    frame_29->setFrameShadow(QFrame::Raised);

    QVBoxLayout* verticalLayout_60 = new QVBoxLayout(frame_29);
    QLabel* trsID = new QLabel(frame_29);

    verticalLayout_60->addWidget(trsID, 0, Qt::AlignHCenter);

    QLabel* costTrs = new QLabel(frame_29);
    costTrs->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    verticalLayout_60->addWidget(costTrs, 0, Qt::AlignHCenter);

    QLabel* rangeTrs = new QLabel(frame_29);
    rangeTrs->setObjectName(QString::fromUtf8("rangeTrs"));
    rangeTrs->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(21, 21, 21);\n"
"	font: 12px \"Google Sans\";\n"
"}"));

    verticalLayout_60->addWidget(rangeTrs, 0, Qt::AlignHCenter);


    horizontalLayout_33->addWidget(frame_29);

    QPushButton* btn = new QPushButton(modelFrameTrsB);
    btn->setObjectName(QString::fromUtf8("btn"));
    btn->setMinimumSize(QSize(30, 50));
    btn->setMaximumSize(QSize(30, 50));
    QIcon icon11;
    icon11.addFile(QString::fromUtf8("../img/feather/trash.svg"), QSize(), QIcon::Normal, QIcon::Off);
    btn->setIcon(icon11);
    btn->setIconSize(QSize(20, 50));

    horizontalLayout_33->addWidget(btn);

    costTrs->setText("Giá tiền: " + QString::fromStdString(info[1]) + "kVND");
    trsID->setText("Biển số xe: " + QString::fromStdString(info[2]));

    rangeTrs->setText("Địa điểm: " + QString::fromStdString(info[4]));

    info.push_back(to_string(index));
    transportBid.insert(btn, index);
    bookedMenu.insert(btn, horizontalLayout_33);
    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(deleteTransFrame()));

    return modelFrameTrsB;
}

void easyflight::deleteTransFrame() {
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    int index = transportBid[buttonSender];


    QHBoxLayout* layout = bookedMenu[buttonSender];
    while (layout->count() != 0) {
        QLayoutItem* item = layout->takeAt(0);
        delete item->widget();
    }
    facade->cancelTrs(index);
}

void easyflight::on_pushButton_purchaseConfirmTransport_clicked()
{
    vector<string> info = transportInfo[tempBtn];

    vector<Transport*> booked = facade->bookTransport(info[4], info.back(), stoi(info[3]), choices[0]);


    if (!booked.empty()) {
        QMessageBox::information(this, " ", "Đặt phương tiện thành công!");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {
        QMessageBox::information(this, " ", "Đặt phương tiện thất bại!");
        ui->stackedWidget->setCurrentIndex(12);
    }
}

