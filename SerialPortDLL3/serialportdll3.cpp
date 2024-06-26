#include "serialportdll3.h"
#include <QtSerialPort>
#include <qiodevice.h>

SerialPortDLL3::SerialPortDLL3()
{
    qDebug() << "Available serial ports:";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port:" << serialPortInfo.portName();
    }

    serialPort = new QSerialPort();

    // Aseta sarjaportin asetukset
    serialPort->setPortName("COM6"); // Korvaa tarvittaessa porttinimi
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    // Liitetään readyRead-signaali lukemistoimintoon
    connect(serialPort, &QSerialPort::readyRead, this, &SerialPortDLL3::serialSlot);

    // Avaa sarjaportti lukua varten
    if (!serialPort->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open serial port:" << serialPort->errorString();
        delete serialPort;
        return;
    }

    qDebug() << "Serial port opened successfully.";
}

void SerialPortDLL3::serialSlot()
{
   QByteArray data = serialPort->readAll();
   cardNum = QString::fromUtf8(data);
   static const QRegularExpression regExp("\r\n-");
   static const QRegularExpression regExp2("\r\n>");
   cardNum.remove(regExp);
   cardNum.remove(regExp2);

   qDebug() << "Received data:" << cardNum;
   emit sendData(cardNum);
}

SerialPortDLL3::~SerialPortDLL3() {
    serialPort->close();
    delete serialPort;
}
