#include "transactionswidget.h"
#include "qjsonarray.h"
#include "ui_transactionswidget.h"
#include "QString"

TransactionsWidget::TransactionsWidget(QWidget *parent)
    : QStackedWidget(parent)
    , ui(new Ui::TransactionsWidget)
{
    ui->setupUi(this);

    ptr = new networkComponents;
    static const bool networkComponentsConnection = connect(ptr, &networkComponents::loadTransactionWidget,this, &TransactionsWidget::showData);
    qDebug() << "TransactionWidget Connection was successful?" << networkComponentsConnection;
    loadedTransactionCount = 0;
}

TransactionsWidget::~TransactionsWidget()
{
    delete ptr;
}

void TransactionsWidget::showData()
{
    qDebug() << "Fired transactionwidget func";

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"Date", "Amount", "Transaction ID"});

    QJsonArray transactionArray = ptr->transactionHistory.array();
    int totalTransactions = transactionArray.size();
    int transactionsToShow = qMin(totalTransactions, loadedTransactionCount + 10);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setRowCount(transactionsToShow);
    ui->tableWidget->verticalHeader()->setVisible(false);

    for (int i = 0; i < transactionsToShow && (totalTransactions - 1 - i) >= 0; ++i) {
        QJsonObject object = transactionArray[totalTransactions - 1 - i].toObject();

        QString date = object.value("date").toString();
        double amount = object.value("amount").toDouble();
        int accountId = object.value("idtransactionHistory").toInt();

        QTableWidgetItem *dateItem = new QTableWidgetItem(date);
        QTableWidgetItem *amountItem = new QTableWidgetItem(QString::number(amount) + "€");
        QTableWidgetItem *idtransactionItem = new QTableWidgetItem(QString::number(accountId));
        dateItem->setFlags(dateItem->flags() ^ Qt::ItemIsEditable);
        amountItem->setFlags(amountItem->flags() ^ Qt::ItemIsEditable);
        idtransactionItem->setFlags(idtransactionItem->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(i, 0, dateItem);
        ui->tableWidget->setItem(i, 1, amountItem);
        ui->tableWidget->setItem(i, 2, idtransactionItem);
    }
    loadedTransactionCount = transactionsToShow;
    setCurrentIndex(2);
}

void TransactionsWidget::sendReq()
{
    qDebug()<<"sending transactions history request from front-end";
    ptr->getTransactionHistory();
}

void TransactionsWidget::on_btnMore_clicked()
{
    showData();
}

