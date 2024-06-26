#ifndef SERIALPORTDLL3_H
#define SERIALPORTDLL3_H

#include "SerialPortDLL3_global.h"
#include <QObject>
#include <QSerialPort>
#include <qstring.h>

class SERIALPORTDLL3_EXPORT SerialPortDLL3 : public QObject
{
    Q_OBJECT
public:
    SerialPortDLL3();
    ~SerialPortDLL3();

private slots:
    void serialSlot();

private:
    QSerialPort *serialPort;
    QString cardNum;
signals:
    void sendData(QString);

};

#endif // SERIALPORTDLL_H
