QT       += core gui qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Calculator.cpp \
    admin_screen.cpp \
    buyer_screen.cpp \
    cal_screen.cpp \
    logup.cpp \
    main.cpp \
    login.cpp \
    myinfo.cpp \
    seller_screen.cpp \
    user_screen.cpp \
    users.cpp

HEADERS += \
    Calculator.h \
    admin_screen.h \
    buyer_screen.h \
    cal_screen.h \
    global.h \
    login.h \
    logup.h \
    myinfo.h \
    seller_screen.h \
    user_screen.h \
    users.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
