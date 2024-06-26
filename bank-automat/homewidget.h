#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QStackedWidget>
#include "networkcomponents.h"
#include "withdrawwidget.h"
namespace Ui {
class HomeWidget;
}

class HomeWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);
    ~HomeWidget();
    networkComponents *networkPtr;
    WithdrawWidget *withdrawPtr;
private slots:
    void showAccountInformation();
    void handleSendUserNameToMain();
private:
    Ui::HomeWidget *ui;
    void sendReq();
signals:
    void goToWithdraw();
    void sendUserNameToMain(QString);
    void sendMoneyToMain(QString, QString);
};

#endif // HOMEWIDGET_H
