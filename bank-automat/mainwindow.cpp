#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <qprocess.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Bank-automat");

    // sivu hommaan napit
    connect(ui->btnHomeSide, SIGNAL(clicked()), this, SLOT(showHome()));
    connect(ui->btnCreditSide, SIGNAL(clicked()), this, SLOT(credit()));
    connect(ui->btnTransactionsSide, SIGNAL(clicked()), this, SLOT(transactions()));
    connect(ui->btnWithdrawSide, SIGNAL(clicked()), this, SLOT(withdraw()));
    connect(ui->btnLogoutSide, SIGNAL(clicked()), this, SLOT(logout()));

    //networkPtr = new networkComponents;
    //connect(networkPtr, &networkComponents::userInfoReadyRead,this, &MainWindow::showUserName);

    creditPage = new CreditWidget;
    connect(creditPage, &CreditWidget::sendMoneyToMain, this, &MainWindow::showMoneyInformation);
    transactionsPage = new TransactionsWidget;
    withdrawPage = new WithdrawWidget;
    connect(withdrawPage, &WithdrawWidget::sendMoneyToMain, this, &MainWindow::showMoneyInformation);
    //login
    loginWindowPtr = new LoginWindow;
    loginWindowPtr->show();
    static const bool networkComponentsConnection = connect(loginWindowPtr, &LoginWindow::showMainWindow,this, &MainWindow::login);
    qDebug() << "MainWindow Connection was successful" << networkComponentsConnection;
    //timer setup
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showHome()));
    connect(this , SIGNAL(resetTimerSignal()), this, SLOT(resetTimer()));
    //event
    qApp->installEventFilter(this);
    //flagit
    onHomePage = false;
    userLoggedIn = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showHome(){
    if (userLoggedIn) {
        onHomePage = true;
        timer->stop();
        ui->stackedWidget->setCurrentIndex(homeIndex);
    }
}

void MainWindow::login(){
    userLoggedIn = true;
    home();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonRelease && !onHomePage && userLoggedIn) {
        emit resetTimerSignal();
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::resetTimer() {
    timer->start(30000);
    qDebug() << "Timer restarted...";
}

//buttoneihin yhistetyt methodit
void MainWindow::credit(){
    if (onHomePage && userLoggedIn) {
        emit resetTimerSignal();
        onHomePage = false;
    }
    creditIndex = ui->stackedWidget->addWidget(creditPage);
    ui->stackedWidget->setCurrentIndex(creditIndex);
    creditPage->setCurrentIndex(0);
}

void MainWindow::transactions()
{
    if (onHomePage && userLoggedIn) {
        emit resetTimerSignal();
        onHomePage = false;
    }
    transactionsPage->sendReq();
    transactionsIndex = ui->stackedWidget->addWidget(transactionsPage);
    ui->stackedWidget->setCurrentIndex(transactionsIndex);
    //transactionsPage->setCurrentIndex(1);
}

void MainWindow::showUserInformation(QString name)
{
    qDebug()<<"showing username"<<name;
    ui->labelUser->setText(name);
}

void MainWindow::showMoneyInformation(QString balance, QString creditLimit)
{
    ui->labelCredit->setText("current credit: " + creditLimit+ "€");
    ui->labelMoney->setText("balance: " + balance + "€");
}

void MainWindow::withdraw(){
    if (onHomePage && userLoggedIn) {
        emit resetTimerSignal();
        onHomePage = false;
    }
    withdrawIndex = ui->stackedWidget->addWidget(withdrawPage);
    ui->stackedWidget->setCurrentIndex(withdrawIndex);
    withdrawPage->setCurrentIndex(0);
}

void MainWindow::home(){
    homePage = new HomeWidget;
    homeIndex = ui->stackedWidget->addWidget(homePage);
    showHome();
    homePage->setCurrentIndex(0);
    //stackedwidget signaalit mainwindowille
    connect(homePage, SIGNAL(goToWithdraw()), this, SLOT(withdraw()));
    connect(homePage, &HomeWidget::sendUserNameToMain, this, &MainWindow::showUserInformation);
    connect(homePage, &HomeWidget::sendMoneyToMain, this, &MainWindow::showMoneyInformation);

    //connect(withdrawPage, &WithdrawWidget::sendMoneyToMain, this, &MainWindow::showMoneyInformation);
    ui->stackedWidget->setCurrentIndex(homeIndex);

    //delete later if i care
    loginWindowPtr->close();

    //networkPtr->getUserInfo();
    this->show();

    qDebug()<<"Home screen";
}

void MainWindow::logout(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Logout", "Are you sure you want to logout?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << ("Yes, exit.");
        qApp->exit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    } else {
        qDebug() << ("No.");
    }
}




