#include "homewidget.h"
#include "ui_homewidget.h"

HomeWidget::HomeWidget(QWidget *parent)
    : QStackedWidget(parent)
    , ui(new Ui::HomeWidget)
{
    ui->setupUi(this);
    connect(ui->btnGoToWithdraw, SIGNAL(clicked()), this, SIGNAL(goToWithdraw()));

    networkPtr = new networkComponents;
    static const bool networkComponentsConnection = connect(networkPtr, &networkComponents::accountInfoReadyRead,this, &HomeWidget::showAccountInformation);
    connect(networkPtr, &networkComponents::userInfoReadyRead,this, &HomeWidget::handleSendUserNameToMain);
    qDebug() << "HomeWidget Connection was successful?" << networkComponentsConnection;

    //withdrawPtr = new WithdrawWidget;
    //connect(withdrawPtr, &WithdrawWidget::updateBalance, this, &HomeWidget::sendReq);

    this->sendReq();
}

HomeWidget::~HomeWidget()
{
    delete ui;
}

void HomeWidget::showAccountInformation()
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

void HomeWidget::handleSendUserNameToMain()
{
    QString fullName = networkPtr->userInformation.value("fName").toString();
    fullName += " ";
    fullName += networkPtr->userInformation.value("lName").toString();
    ui->label->setText("Welcome, " + fullName + ". " + "Would you like to make a withdrawal?");
    emit sendUserNameToMain(fullName);
}

void HomeWidget::sendReq()
{
    qDebug()<<"sending account info request from front-end";
    networkPtr->getAccountInfo();
}

