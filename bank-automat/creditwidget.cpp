#include "creditwidget.h"
#include "ui_creditwidget.h"
#include <QMessageBox>
#include <qregularexpression.h>

CreditWidget::CreditWidget(QWidget *parent)
    : QStackedWidget(parent)
    , ui(new Ui::CreditWidget)
{
    ui->setupUi(this);
    connect(ui->btnConfirm, SIGNAL(clicked()), this , SLOT(enterValue()));

    networkPtr = new networkComponents;

    static const bool myConnection = connect(networkPtr, &networkComponents::loadLoanSuccesful,this, &CreditWidget::loanSuccess);
    connect(networkPtr, &networkComponents::accountInfoReadyRead,this, &CreditWidget::showAccountInformation);
    connect(networkPtr, &networkComponents::errorMsg,this, &CreditWidget::showError);
    qDebug() << "TransactionWidget Connection was successful" << myConnection;
}

CreditWidget::~CreditWidget()
{
    delete networkPtr;
}

void CreditWidget::enterValue(){
    bool integer = 0;
    //€, e ,E check
    QString value = ui->lineEdit->text();
    value.remove(QChar(0x20AC));
    static const  QRegularExpression regExp("e", QRegularExpression::CaseInsensitiveOption);
    value.remove(regExp);
    int pureValue = value.toInt(&integer);

    if (integer) {
        confirmCredit(pureValue);
    }else{
        qDebug() << ("Give euro amount");
    }
}

void CreditWidget::confirmCredit(int amount) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Credit", QString("Do you really want to take %1€ loan?").arg(amount),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << QString("Take a loan of %1 euro was confirmed").arg(amount);
        networkPtr->takeALoan(amount);
    } else {
        qDebug() << QString("Take a loan of euro was cancelled").arg(amount);
    }
    ui->lineEdit->clear();
}

void CreditWidget::loanSuccess()
{
    qDebug()<<"Loan granted";
    sendReq();
}

void CreditWidget::sendReq()
{
    qDebug()<<"sending account info request from front-end";
    networkPtr->getAccountInfo();
}

void CreditWidget::showAccountInformation()
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

void CreditWidget::showError()
{
    popUpPtr = new PopUp;
    popUpPtr->showPopup("Not enough creditLimit");
    qDebug()<<"Not enough creditLimit";
}
