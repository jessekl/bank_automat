#include "widgetrefresher.h"

widgetRefresher::widgetRefresher() {

}
widgetRefresher::~widgetRefresher() {
    qDebug()<<"deleted widget refresher";
}

void widgetRefresher::handleTransactionsPageRefresh()
{
    qDebug()<<"refreshed transactionsPage";
    emit refresh();
}

void widgetRefresher::handleWithdrawPageRefresh()
{
    qDebug()<<"refreshed withdrawPage";
    emit refresh();
}

void widgetRefresher::handleCreditPageRefresh()
{
    qDebug()<<"refreshed creditPage";
    emit refresh();
}
