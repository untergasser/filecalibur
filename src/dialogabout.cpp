#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QString ver, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    ui->labelVersion->setText(ver);
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::on_buttonBox_accepted()
{
    this->close();
}
