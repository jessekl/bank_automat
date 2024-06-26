#include "networkcomponents.h"

int networkComponents::idUser = 0;
int networkComponents::idAccount = 0;
QString networkComponents::pinNumber = 0;
QString networkComponents::cardNumber = 0;
int networkComponents::balance = 0;
int networkComponents::creditLimit = 0;
QString networkComponents::requestType = 0;
QByteArray networkComponents::webtoken = 0;
int networkComponents::amountForTransactionHistory = 0;

networkComponents::networkComponents()
{
    ptr = new RestApiDLL;


    //send data as signal
    connect(ptr, &RestApiDLL::sendDataToMain, this, &networkComponents::handleDataRead);
}

networkComponents::~networkComponents()
{
    delete ptr;
}

//function below is called when data is available to process

void networkComponents::handleDataRead(QByteArray data)
{
    //convert bytearray to json document
    QJsonParseError JsonError;
    QJsonDocument document = QJsonDocument::fromJson(data, &JsonError);

    if(requestType == "handleLogin" && data == "false"){
        emit loadWrongPinError();
    }
    if(requestType == "handleLogin" && data != "false")
    {
        QJsonObject temp = document.object();
        webtoken = temp.value("token").toString().toUtf8();
        pinNumber = temp.value("pinNumber").toString();

        this->getAccountId();
    }
    else
    {
        if(JsonError.error != QJsonParseError::NoError)
        {
            qDebug()<<"Error in json data" << JsonError.errorString();
            return;
        }

        if(document.isEmpty())
        {
            qDebug()<<"Empty JSON Object";
        }
        else
        {

            //if many entries like an array is needed do as shown below
            if(requestType == "getTransactionHistory" && idAccount){

                qDebug()<<"Match was found, for account number: " <<idAccount;
                transactionHistory = document;
                qDebug()<<transactionHistory;
                emit loadTransactionWidget();
                qDebug()<<"Emitted transaction widget";
                return;
            }
            if(requestType == "addTransaction" && idAccount){
                QJsonObject object = document[0].toObject();
                if(object.value("success").toString() == "false"){
                    qDebug()<<"User doesnt have enough balance";
                    emit errorMsg();
                    return;
                }else{
                    qDebug()<<"Transaction made, for account number: " <<idAccount;
                    this->addEntryToTransactionHistory();
                    emit loadTransactionSuccesful();
                    qDebug()<<"Emitted transaction successful";

                }
                return;
            }
            if(requestType == "takeALoan" && idAccount){
                QJsonObject object = document[0].toObject();
                if(object.value("success").toString() == "false"){
                    qDebug()<<"User doesnt have enough creditLimit";
                    emit errorMsg();
                    return;
                }else{
                    qDebug()<<"Loan taken, for account number: " <<idAccount;
                    emit loadLoanSuccesful();
                    qDebug()<<"Emitted credit widget";
                }
                return;
            }
            //Iterate all entries of the document array
            //Thus we can for example search for a matching entry for values like cardNumber through all of the cards in db
            //Note that it only works if we want 1 entry


            for(int i = 0; i<=(int)sizeof(document); i++)
            {
                QJsonObject object = document[i].toObject();
                //if(requestType == "getAccountId" && object.value("pinNumber").toString() == pinNumber && object.value("cardNumber").toInt() == cardNumber){ //toInt poistettu sen jälkeen kun cardNum vaihettu qstring
                if(requestType == "getAccountId" && object.value("pinNumber").toString() == pinNumber && object.value("cardNumber") == cardNumber){
                    idAccount = object.value("idaccount").toInt();
                    qDebug()<<"Match was found, account id: " <<idAccount;

                    this->getAccountInfo();
                    return;
                }
                if(requestType == "getAccountInformation" && object.value("idaccount").toInt() == idAccount){

                    idUser = object.value("iduser").toInt();
                    balance = object.value("balance").toString().toInt();
                    creditLimit = object.value("creditLimit").toString().toInt();
                    qDebug()<<"Account information was found for user id: " <<idUser;

                    accountInformation = object;
                    emit accountInfoReadyRead();
                    emit loadMainWindow();
                    return;
                }
                if(requestType == "getUserInformation" && object.value("iduser").toInt() == idUser){
                    idUser = object.value("iduser").toInt();
                    qDebug()<<"User information was found for user id: " <<idUser;
                    userInformation = object;

                    emit userInfoReadyRead();
                    return;
                }
            }
        }
    }

}

//Creating two functions one, which sends the request
//and other that is called from the emitted function which is called when the data is readily available

//GET requests

void networkComponents::getAccountInfo()
{
    qDebug()<<"Getting account information...";
    requestType = "getAccountInformation";

    ptr->get("http://127.0.0.1:3000/account", webtoken);
}

void networkComponents::getAccountId()
{

    qDebug()<<"get account id";
    requestType = "getAccountId";

    ptr->get("http://127.0.0.1:3000/card", webtoken);
}

void networkComponents::getUserInfo()
{

    requestType = "getUserInformation";
    ptr->get("http://127.0.0.1:3000/user", webtoken);
}

void networkComponents::getTransactionHistory()
{
    qDebug()<<"Requested transactionhistory";
    requestType = "getTransactionHistory";
    ptr->getTransactionHistory("http://127.0.0.1:3000/transactionHistory/getByAccountId/" + QString::number(idAccount), webtoken);
}

//POST requests

void networkComponents::handleLogin(QString pin, QString cardNum)
{

    QJsonObject obj;
    obj["pinNumber"] = pin;
    obj["cardNumber"] = cardNum;

    //pinNumber = pin.toInt();
    cardNumber = cardNum;

    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();


    qDebug()<<pin<<cardNum;
    requestType = "handleLogin";

    //this request should give us webtoken as response
    ptr->post("http://127.0.0.1:3000/card/login", data, webtoken);
}

void networkComponents::takeALoan(int amount)
{
    requestType = "takeALoan";
    QJsonObject obj;
    obj["creditAmount"] = amount;

    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    ptr->addTransaction("http://127.0.0.1:3000/account/" + QString::number(idAccount) + "/credit", data, webtoken);
}


void networkComponents::addTransaction(int amount)
{
    requestType = "addTransaction";
    //amount to minus for accurate transactionHistory
    amountForTransactionHistory = -amount;

    QJsonObject obj;
    obj["amount"] = amount;

    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    qDebug()<<idAccount;
    ptr->addTransaction("http://127.0.0.1:3000/account/" + QString::number(idAccount) + "/debit", data, webtoken);
}

void networkComponents::addEntryToTransactionHistory()
{
    requestType = "addEntryToTransactionHistory";

    QJsonObject obj;
    obj["amount"] = amountForTransactionHistory;
    obj["idaccount"] = idAccount;

    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    qDebug()<<idAccount;
    ptr->addEntryToTransHistory("http://127.0.0.1:3000/transactionHistory/", data, webtoken);
}
