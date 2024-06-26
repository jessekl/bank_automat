#include "restapidll.h"

RestApiDLL::RestApiDLL()
{
    connect(&manager, &QNetworkAccessManager::authenticationRequired, this, &RestApiDLL::authenticationRequired);
    connect(&manager, &QNetworkAccessManager::encrypted, this, &RestApiDLL::encrypted);
    connect(&manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &RestApiDLL::preSharedKeyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &RestApiDLL::sslErrors);
}

RestApiDLL::~RestApiDLL()
{
}

void RestApiDLL::get(QString location, QByteArray webtoken)
{
    qInfo() << "Getting from server..";
    //webtoken for request
    QNetworkRequest req = QNetworkRequest(QUrl(location));
    req.setRawHeader(QByteArray("Authorization"),(webtoken));

    QNetworkReply* reply = manager.get(req);
    connect(reply, &QNetworkReply::readyRead, this, &RestApiDLL::readyRead);

}

void RestApiDLL::post(QString location, QByteArray data, QByteArray webtoken)
{
    qInfo() << "Posting to a server..";

    QNetworkRequest req = QNetworkRequest(QUrl(location));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setRawHeader(QByteArray("Authorization"),(webtoken));

    QNetworkReply* reply = manager.post(req, data);
    connect(reply, &QNetworkReply::readyRead, this, &RestApiDLL::readyRead);
}

void RestApiDLL::put(QString location, QByteArray data, QByteArray webtoken)
{
    qInfo() << "Updating data to the server..";

    QNetworkRequest req = QNetworkRequest(QUrl(location));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    req.setRawHeader(QByteArray("Authorization"),(webtoken));
    qDebug()<<webtoken;

    QNetworkReply* reply = manager.put(req, data);
    connect(reply, &QNetworkReply::readyRead, this, &RestApiDLL::readyRead);
}

void RestApiDLL::readyRead()
{
    qInfo()<<"ReadyRead";

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if(reply)
    {
        QByteArray data;
        data = reply->readAll();
        emit sendDataToMain(data);
    }
}

void RestApiDLL::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
    qInfo()<<"authenticationRequired";
}

void RestApiDLL::encrypted(QNetworkReply *reply)
{
    Q_UNUSED(reply);
    qInfo()<<"encrypted";
}

void RestApiDLL::finished(QNetworkReply *reply)
{
    Q_UNUSED(reply);
    qInfo()<<"finished";
}


void RestApiDLL::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
    qInfo()<<"preSharedKeyAuthenticationRequired";
}

void RestApiDLL::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    Q_UNUSED(errors);
    qInfo()<<"sslErrors";
}

void RestApiDLL::addTransaction(QString location, QByteArray data, QByteArray webtoken)
{
    this->put(location, data, webtoken);
}

void RestApiDLL::addNewCard(QString location, QByteArray data, QByteArray webtoken)
{
    this->post(location, data, webtoken);
}

void RestApiDLL::changePinNumber(QString location, QByteArray data, QByteArray webtoken)
{
    this->put(location, data, webtoken);
}

void RestApiDLL::getTransactionHistory(QString location, QByteArray webtoken)
{
    this->get(location, webtoken);
}

void RestApiDLL::getUserData(QString location, QByteArray webtoken)
{
    this->get(location, webtoken);
}

void RestApiDLL::getAccount(QString location, QByteArray webtoken)
{
    this->get(location, webtoken);
}

void RestApiDLL::checkCardData(QString location, QByteArray webtoken)
{
    this->get(location, webtoken);
}

void RestApiDLL::addEntryToTransHistory(QString location, QByteArray data, QByteArray webtoken)
{
    this->post(location, data, webtoken);
}
