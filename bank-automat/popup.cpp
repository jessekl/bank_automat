#include "popup.h"
#include "ui_popup.h"

PopUp::PopUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PopUp)
{
    ui->setupUi(this);
}

PopUp::~PopUp()
{
    delete ui;
}

void PopUp::showPopup(QString txt)
{
    ui->label->setText(txt);
    this->show();
}

void PopUp::on_pushButton_clicked()
{
    this->deleteLater();
}

