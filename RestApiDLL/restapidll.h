#ifndef RESTAPIDLL_H
#define RESTAPIDLL_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkProxy>

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include "RestApiDLL_global.h"

class RESTAPIDLL_EXPORT RestApiDLL : public QObject
{
    Q_OBJECT
public:
    RestApiDLL();
    ~RestApiDLL();
    void addTransaction(QString location, QByteArray data, QByteArray);
    void addNewCard(QString location, QByteArray data, QByteArray);
    void changePinNumber(QString location, QByteArray data, QByteArray);
    void getTransactionHistory(QString location, QByteArray);
    void getUserData(QString location, QByteArray);
    void getAccount(QString location, QByteArray);
    void checkCardData(QString location, QByteArray);
    void addEntryToTransHistory(QString location, QByteArray data, QByteArray);
public slots:
    void get(QString location, QByteArray webtoken);
    void post(QString location, QByteArray data, QByteArray webtoken);
    void put(QString location, QByteArray data, QByteArray webtoken);
private slots:
    void readyRead();
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);
    void finished(QNetworkReply *reply);
    void preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
signals:
    void sendDataToMain(QByteArray);
private:
    QNetworkAccessManager manager;

};

#endif // RESTAPIDLL_H
