#ifndef TRANSACTIONSWIDGET_H
#define TRANSACTIONSWIDGET_H

#include <QStackedWidget>
#include "networkcomponents.h"

namespace Ui {
class TransactionsWidget;
}

class TransactionsWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit TransactionsWidget(QWidget *parent = nullptr);
    ~TransactionsWidget();

    networkComponents *ptr;
    void sendReq();
private:
    Ui::TransactionsWidget *ui;
    int loadedTransactionCount;

private slots:
    void showData();
    void on_btnMore_clicked();
};


#endif // TRANSACTIONSWIDGET_H
