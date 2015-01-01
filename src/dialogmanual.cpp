#include "dialogmanual.h"
#include "ui_dialogmanual.h"

DialogManual::DialogManual(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogManual)
{
    ui->setupUi(this);
}

DialogManual::~DialogManual()
{
    delete ui;
}

void DialogManual::setManual(QString text)
{
    ui->textEdit->setHtml(text);
}
