#include "withdrawwidget.h"
#include "qregularexpression.h"
#include "ui_withdrawwidget.h"
#include <QMessageBox>

WithdrawWidget::WithdrawWidget(QWidget *parent)
    : QStackedWidget(parent)
    , ui(new Ui::withdrawWidget)
{
    ui->setupUi(this);
    connect(ui->btnOther, SIGNAL(clicked()), this, SLOT(other()));
    connect(ui->btn5, SIGNAL(clicked()), this, SLOT(value5()));
    connect(ui->btn10, SIGNAL(clicked()), this, SLOT(value10()));
    connect(ui->btn25, SIGNAL(clicked()), this, SLOT(value25()));
    connect(ui->btn50, SIGNAL(clicked()), this, SLOT(value50()));
    connect(ui->btn100, SIGNAL(clicked()), this, SLOT(value100()));
    connect(ui->btnEnter, SIGNAL(clicked()), this, SLOT(enterValue()));

    networkPtr = new networkComponents;
    static const bool myConnection = connect(networkPtr, &networkComponents::loadTransactionSuccesful,this, &WithdrawWidget::transactionSuccesful);
    connect(networkPtr, &networkComponents::errorMsg,this, &WithdrawWidget::showError);
    connect(networkPtr, &networkComponents::accountInfoReadyRead,this, &WithdrawWidget::showAccountInformation);
    qDebug() << "TransactionWidget Connection was successful" << myConnection;
}

WithdrawWidget::~WithdrawWidget()
{
    delete networkPtr;
}

void WithdrawWidget::other()
{
    qDebug() << ("other");
    setCurrentIndex(1);
}

void WithdrawWidget::value5()
{
   // qDebug() << ("5 euro");
   // networkPtr->addTransaction(5);
    confirmWithdraw(5);
}

void WithdrawWidget::value10()
{
    //qDebug() << ("10 euro");
    //networkPtr->addTransaction(10);
    confirmWithdraw(10);
}

void WithdrawWidget::value25()
{
    //qDebug() << ("25 euro");
    //networkPtr->addTransaction(25);
    confirmWithdraw(25);
}

void WithdrawWidget::value50()
{
   // qDebug() << ("50 euro");
    //networkPtr->addTransaction(50);
    confirmWithdraw(50);
}

void WithdrawWidget::value100()
{
   //qDebug() << ("100 euro");
    //networkPtr->addTransaction(100);
    confirmWithdraw(100);
}

//lineEdittiin annettu numero tarkistetaan
void WithdrawWidget::enterValue()
{
    bool integer = 0;
    //€, e ,E check
    QString value = ui->lineEdit->text();
    value.remove(QChar(0x20AC));
    static const  QRegularExpression regExp("e", QRegularExpression::CaseInsensitiveOption);
    value.remove(regExp);
    int pureValue = value.toInt(&integer);
    if (integer) {
        if (pureValue <= 1000) {
            //qDebug() << (pureValue);
            //networkPtr->addTransaction(pureValue);
            confirmWithdraw(pureValue);
        }else {
            qDebug() << ("Maximum you can withdraw is 1000€");
        }
    }else{
        qDebug() << ("Give euro amount");
    }
    ui->lineEdit->clear();
}

void WithdrawWidget::confirmWithdraw(int amount) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Withdraw", QString("Do you really want to withdraw %1€?").arg(amount),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << QString("Withdraw %1 euro was confirmed").arg(amount);
        // If confirmed, proceed with the transaction
        networkPtr->addTransaction(amount);
    } else {
        qDebug() << QString("Withdraw %1 euro was cancelled").arg(amount);
        // If cancelled, do nothing or handle as needed
    }
}

void WithdrawWidget::showError()
{
    popUpPtr = new PopUp;
    popUpPtr->showPopup("Not enough balance");
    qDebug()<<"not enough balance";
}

void WithdrawWidget::transactionSuccesful()
{
    qDebug()<<"Transaction succesful";
    sendReq();
}

void WithdrawWidget::sendReq()
{
    qDebug()<<"sending account info request from front-end";
    networkPtr->getAccountInfo();
}

void WithdrawWidget::showAccountInformation()
{
    qDebug()<<"showing user info";
    qDebug()<<networkPtr->accountInformation<<"user info";
    //ui->efefef->setText(networkPtr->accountInformation.value("balance").toString());
    //ui->creditLabel->setText(networkPtr->accountInformation.value("creditLimit").toString());
    QString balance = networkPtr->accountInformation.value("balance").toString();
    QString creditLimit = networkPtr->accountInformation.value("creditLimit").toString();
    emit sendMoneyToMain(balance, creditLimit);
    networkPtr->getUserInfo();
}
