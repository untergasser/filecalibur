#include "dialogerrormessage.h"
#include "ui_dialogerrormessage.h"

DialogErrorMessage::DialogErrorMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogErrorMessage)
{
    ui->setupUi(this);
}

DialogErrorMessage::~DialogErrorMessage()
{
    delete ui;
}

void DialogErrorMessage::newErr(QString err)
{
    error << err;
}

void DialogErrorMessage::addLast(QString err)
{
    QString modify;
    modify = error.at(error.size()-1);
    modify.append(err);
    error.replace(error.size()-1, modify);
}

void DialogErrorMessage::addLast(int err)
{
    QString modify;
    QString number;
    modify = error.at(error.size()-1);
    number.setNum(err);
    modify.append(number);
    error.replace(error.size()-1, modify);
}

void DialogErrorMessage::checkForErrors()
{
    if (error.size() != 0) {
        ui->plainTextEdit->clear();
        for (int i = 0; i < error.size(); ++i) {
            QString ErrText;
            QString number;
            ErrText = "Error ";
            number.setNum(i + 1);
            ErrText.append(number);
            ErrText.append(":\n");
            ErrText.append(error.at(i).toLocal8Bit().constData());
            ErrText.append("\n");
            ui->plainTextEdit->appendPlainText(ErrText);
        }
        this->show();
    }
}
