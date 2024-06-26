#include "loginwindow.h"
#include "ui_loginwindow.h"


LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    //connect(ui->btnSkip,SIGNAL(clicked()),this, SLOT(skipLogin())); // debugging
    ui->stackedWidget->setCurrentIndex(0);

    networkPtr = new networkComponents;
    static const bool networkComponentsConnection = connect(networkPtr, &networkComponents::loadMainWindow,this, &LoginWindow::showHome);
    connect(networkPtr, &networkComponents::loadWrongPinError,this, &LoginWindow::generateError);
    qDebug() << "MainWindow Connection was successful : " << networkComponentsConnection;

    serialPtr = new SerialPortDLL3;
    static const bool test = connect(serialPtr,&SerialPortDLL3::sendData, this, &LoginWindow::readCardNum);
    qDebug() << "SerialPortDLL3 Connection was " << test;
    loginInit();
}

/*void LoginWindow::skipLogin(){
    //this is for debugging purposes
    cardNum = "06000623A6";
    ui->stackedWidget->setCurrentIndex(1);
}*/

void LoginWindow::generateError()
{
    ui->lineEdit->setText("Wrong PIN Number!");
    stars = "";
    pin = "";
}

LoginWindow::~LoginWindow()
{
    delete networkPtr;
}

void LoginWindow::loginInit()
{
    connect(ui->btn0,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn1,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn2,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn3,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn4,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn5,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn6,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn7,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn8,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn9,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn10,SIGNAL(clicked()),this, SLOT(keypad()));
    connect(ui->btn11,SIGNAL(clicked()),this, SLOT(keypad()));
}


void LoginWindow::keypad(){
    QObject* pObject = sender();
    QString name = pObject->objectName();

    if(pin.size() <= 3 && name.size() < 5)
    {
        stars += "*";
        ui->lineEdit->setText(stars);
        pin += name[3];
        qDebug()<<pin;
    }
    if(pin.size() == 4 && name == "btn10")
    {
        qDebug()<<"login with pin:"<<pin<<"and card num :"<<cardNum;
        networkPtr->handleLogin(pin, cardNum);
    }
    if(name == "btn11")
    {
        pin.chop(1);
        stars.chop(1);
        ui->lineEdit->setText(stars);
        qDebug()<<pin;
    }
}

void LoginWindow::showHome()
{
    emit showMainWindow();
}

void LoginWindow::readCardNum(QString num)
{
    qDebug()<<"login "<<num;
    cardNum = num;
    ui->stackedWidget->setCurrentIndex(1);
}
