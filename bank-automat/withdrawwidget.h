#ifndef WITHDRAWWIDGET_H
#define WITHDRAWWIDGET_H

#include <QStackedWidget>
#include "networkcomponents.h"
#include "popup.h"
namespace Ui {
class withdrawWidget;
}

class WithdrawWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit WithdrawWidget(QWidget *parent = nullptr);
    ~WithdrawWidget();
    networkComponents *networkPtr;
    PopUp *popUpPtr;
private slots:
    void other();
    void value5();
    void value10();
    void value25();
    void value50();
    void value100();
    void enterValue();
    void showError();
private:
    Ui::withdrawWidget *ui;
    void transactionSuccesful();
    void sendReq();
    void showAccountInformation();
    void confirmWithdraw(int);
private slots:
signals:
    void updateBalance();
    void sendMoneyToMain(QString, QString);
};

#endif // WITHDRAWWIDGET_H
