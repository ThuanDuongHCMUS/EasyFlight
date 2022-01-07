QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/Account.cpp \
    core/Chain.cpp \
    core/Facade/Date.cpp \
    core/Facade/Facade.cpp \
    core/Facade/Flight.cpp \
    core/Facade/Hotel.cpp \
    core/Facade/Time.cpp \
    core/Facade/Transport/Bus.cpp \
    core/Facade/Transport/Grab.cpp \
    core/Facade/Transport/Taxi.cpp \
    core/Facade/Transport/Transport.cpp \
    core/Facade/Transport/TransportList.cpp \
    core/LinkedListAccount.cpp \
    core/Login.cpp \
    core/PasswordChecker.cpp \
    core/UserChecker.cpp \
    editpassworddialog.cpp \
    main.cpp \
    easyflight.cpp \
    passwordauthentication.cpp

HEADERS += \
    core/Account.h \
    core/Chain.h \
    core/DateTime.h \
    core/Facade/Date.h \
    core/Facade/Facade.h \
    core/Facade/Flight.h \
    core/Facade/Hotel.h \
    core/Facade/Time.h \
    core/Facade/Transport/Bus.h \
    core/Facade/Transport/Grab.h \
    core/Facade/Transport/Taxi.h \
    core/Facade/Transport/Transport.h \
    core/Facade/Transport/TransportList.h \
    core/LIB.h \
    core/LIBLogin.h \
    core/LinkedListAccount.h \
    core/Login.h \
    core/PasswordChecker.h \
    core/UserChecker.h \
    easyflight.h \
    editpassworddialog.h \
    passwordauthentication.h

FORMS += \
    easyflight.ui \
    editpassworddialog.ui \
    passwordauthentication.ui

TRANSLATIONS += \
    easyflight_vi_VN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    core/flights.json \
    core/hotels.json \
    core/info.json \
    core/list.json
