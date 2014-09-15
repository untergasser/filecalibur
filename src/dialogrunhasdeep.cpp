#include "dialogrunhasdeep.h"
#include "ui_dialogrunhasdeep.h"

DialogRunHasDeep::DialogRunHasDeep(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRunHasDeep)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->pushButton, SIGNAL(released()), this->parent(), SLOT(killHashDeep()));
}

DialogRunHasDeep::~DialogRunHasDeep()
{
    delete ui;
}
