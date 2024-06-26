#ifndef CREDITWIDGET_H
#define CREDITWIDGET_H

#include <QStackedWidget>
#include "networkcomponents.h"
#include "popup.h"
namespace Ui {
class CreditWidget;
}

class CreditWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit CreditWidget(QWidget *parent = nullptr);
    ~CreditWidget();
    networkComponents *networkPtr;
    PopUp *popUpPtr;
private:
    Ui::CreditWidget *ui;
    void sendReq();
    void confirmCredit(int);
private slots:
    void enterValue();
    void loanSuccess();
    void showAccountInformation();
    void showError();
signals:
    void sendMoneyToMain(QString, QString);

};

#endif // CREDITWIDGET_H
