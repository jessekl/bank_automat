#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "networkcomponents.h"
#include "serialportdll3.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    networkComponents *networkPtr;
    SerialPortDLL3 *serialPtr;

private:
    Ui::LoginWindow *ui;
    QString pin;
    QString stars;
    QString cardNum;
private slots:
    void loginInit();
    void keypad();
    void showHome();
    void readCardNum(QString);
    //void skipLogin();
    void generateError();
signals:
    void showMainWindow();
    void sendPinToMain(QString, int);
};

#endif // LOGINWINDOW_H
