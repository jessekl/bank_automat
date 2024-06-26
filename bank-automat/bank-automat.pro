QT += core gui
QT += network
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creditwidget.cpp \
    homewidget.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    networkcomponents.cpp \
    popup.cpp \
    transactionswidget.cpp \
    withdrawwidget.cpp

HEADERS += \
    creditwidget.h \
    homewidget.h \
    loginwindow.h \
    mainwindow.h \
    networkcomponents.h \
    popup.h \
    transactionswidget.h \
    withdrawwidget.h

FORMS += \
    creditwidget.ui \
    homewidget.ui \
    loginwindow.ui \
    mainwindow.ui \
    popup.ui \
    transactionswidget.ui \
    withdrawwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    styles/style.qss




win32: LIBS += -L$$PWD/../RestApiDLL/build/debug/ -lRestApiDLL

#* INCLUDEPATH += $$PWD/../RestApiDLL
DEP*¤ENDPATH += $$PWD/../RestApiDLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/release/ -lRestApiDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/debug/ -lRestApiDLL
else:unix: LIBS += -L$$PWD/../RestApiDLL/build/ -lRestApiDLL

INCLUDEPATH += $$PWD/../RestApiDLL/build
DEPENDPATH += $$PWD/../RestApiDLL/build

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/release/ -lRestApiDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/debug/ -lRestApiDLL
else:unix: LIBS += -L$$PWD/../RestApiDLL/build/ -lRestApiDLL

INCLUDEPATH += $$PWD/../RestApiDLL
DEPENDPATH += $$PWD/../RestApiDLL

win32: LIBS += -L$$PWD/../RestApiDLL/build/debug/ -lRestApiDLL

INCLUDEPATH += $$PWD/../RestApiDLL
DEPENDPATH += $$PWD/../RestApiDLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/release/ -lSerialPortDLL3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/debug/ -lSerialPortDLL3
else:unix: LIBS += -L$$PWD/../SerialPortDLL3/build/ -lSerialPortDLL3

INCLUDEPATH += $$PWD/../SerialPortDLL3
DEPENDPATH += $$PWD/../SerialPortDLL3

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/release/ -lRestApiDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/debug/ -lRestApiDLL
else:unix: LIBS += -L$$PWD/../RestApiDLL/build/ -lRestApiDLL

INCLUDEPATH += $$PWD/../RestApiDLL
DEPENDPATH += $$PWD/../RestApiDLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/release/ -lSerialPortDLL3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/debug/ -lSerialPortDLL3
else:unix: LIBS += -L$$PWD/../SerialPortDLL3/build/ -lSerialPortDLL3

INCLUDEPATH += $$PWD/../SerialPortDLL3
DEPENDPATH += $$PWD/../SerialPortDLL3

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/release/ -lRestApiDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/debug/ -lRestApiDLL
else:unix: LIBS += -L$$PWD/../RestApiDLL/build/ -lRestApiDLL

INCLUDEPATH += $$PWD/../RestApiDLL
DEPENDPATH += $$PWD/../RestApiDLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/release/ -lSerialPortDLL3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/debug/ -lSerialPortDLL3
else:unix: LIBS += -L$$PWD/../SerialPortDLL3/build/ -lSerialPortDLL3

INCLUDEPATH += $$PWD/../SerialPortDLL3
DEPENDPATH += $$PWD/../SerialPortDLL3

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/release/ -lSerialPortDLL3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/debug/ -lSerialPortDLL3
else:unix: LIBS += -L$$PWD/../SerialPortDLL3/build/ -lSerialPortDLL3

INCLUDEPATH += $$PWD/../SerialPortDLL3
DEPENDPATH += $$PWD/../SerialPortDLL3

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/release/ -lRestApiDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/debug/ -lRestApiDLL
else:unix: LIBS += -L$$PWD/../RestApiDLL/build/ -lRestApiDLL

INCLUDEPATH += $$PWD/../RestApiDLL
DEPENDPATH += $$PWD/../RestApiDLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/release/ -lSerialPortDLL3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/debug/ -lSerialPortDLL3
else:unix: LIBS += -L$$PWD/../SerialPortDLL3/build/ -lSerialPortDLL3

INCLUDEPATH += $$PWD/../SerialPortDLL3
DEPENDPATH += $$PWD/../SerialPortDLL3

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/release/ -lSerialPortDLL3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SerialPortDLL3/build/debug/ -lSerialPortDLL3
else:unix: LIBS += -L$$PWD/../SerialPortDLL3/build/ -lSerialPortDLL3

INCLUDEPATH += $$PWD/../SerialPortDLL3
DEPENDPATH += $$PWD/../SerialPortDLL3

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/release/ -lRestApiDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/debug/ -lRestApiDLL
else:unix: LIBS += -L$$PWD/../RestApiDLL/build/ -lRestApiDLL

INCLUDEPATH += $$PWD/../RestApiDLL
DEPENDPATH += $$PWD/../RestApiDLL
