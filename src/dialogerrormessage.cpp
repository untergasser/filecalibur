/****************************************************************************
**
**  (c) Copyright 2014 by Dr. Andreas Untergasser
**      All rights reserved.
**
**  This file is part of Filecalibur.
**
**  Filecalibur is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Filecalibur is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Filecalibur.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

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
