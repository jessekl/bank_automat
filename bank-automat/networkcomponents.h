#ifndef NETWORKCOMPONENTS_H
#define NETWORKCOMPONENTS_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include "restapidll.h"
#include "qjsonarray.h"

class networkComponents : public QObject
{
    Q_OBJECT

public:
    networkComponents();
    ~networkComponents();
    RestApiDLL *ptr;
    void handleLogin(QString, QString);
    void getAccountId();
    void addTransaction(int);
    void getAccountInfo();
    void getUserInfo();
    void getTransactionHistory();
    void logInfo();
    void logTransactionHistory();
    void takeALoan(int);
    void addEntryToTransactionHistory();
    QJsonDocument transactionHistory;
    QJsonObject accountInformation;
    QJsonObject userInformation;
public slots:
    void handleDataRead(QByteArray);
private:
    static int idUser;
    static int idAccount;
    static QString pinNumber;
    static QString cardNumber;
    static int balance;
    static int amountForTransactionHistory;
    static int creditLimit;
    static QString requestType;
    static QByteArray webtoken;
signals:
    void loadTransactionWidget();
    void loadTransactionSuccesful();
    void loadLoanSuccesful();
    void loadMainWindow();
    void loadWrongPinError();
    void accountInfoReadyRead();
    void userInfoReadyRead();
    void moneyUpdate();
    void errorMsg();
};


#endif // NETWORKCOMPONENTS_H
