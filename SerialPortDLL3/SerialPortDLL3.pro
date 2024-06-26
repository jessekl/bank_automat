QT -= gui
QT += serialport
TEMPLATE = lib
DEFINES += SERIALPORTDLL3_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    serialportdll3.cpp

HEADERS += \
    SerialPortDLL3_global.h \
    serialportdll3.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/release/ -lRestApiDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../RestApiDLL/build/debug/ -lRestApiDLL
else:unix: LIBS += -L$$PWD/../RestApiDLL/build/ -lRestApiDLL

INCLUDEPATH += $$PWD/../RestApiDLL
DEPENDPATH += $$PWD/../RestApiDLL
