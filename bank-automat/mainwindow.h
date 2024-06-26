#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include "withdrawwidget.h"
#include "homewidget.h"
#include "transactionswidget.h"
#include "creditwidget.h"
#include "networkcomponents.h"
#include "loginwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *watched, QEvent *event) override;
    LoginWindow *loginWindowPtr;
    networkComponents *networkPtr;
private slots:
    void logout();
    void withdraw();
    void home();
    void credit();
    void transactions();
    void showUserInformation(QString);
    void showMoneyInformation(QString, QString);
    void resetTimer();
    void showHome();
    void login();
private:
    Ui::MainWindow *ui;
    int withdrawIndex;
    WithdrawWidget* withdrawPage;
    int homeIndex;
    HomeWidget* homePage;
    int transactionsIndex;
    TransactionsWidget* transactionsPage;
    int creditIndex;
    CreditWidget* creditPage;
    QTimer *timer;
    bool onHomePage;
    bool userLoggedIn;
protected:
    //void closeEvent(QCloseEvent *event) override;
signals:
    void resetTimerSignal();
};
#endif // MAINWINDOW_H
