#ifndef WIDGETREFRESHER_H
#define WIDGETREFRESHER_H

#include <QObject>
#include "QDebug"

class widgetRefresher : public QObject
{
    Q_OBJECT
public:
    widgetRefresher();
    ~widgetRefresher();
    void handleTransactionsPageRefresh();
    void handleWithdrawPageRefresh();
    void handleCreditPageRefresh();

signals:
    void refresh();
};

#endif // WIDGETREFRESHER_H
