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

#include "dialognegmatch.h"
#include "ui_dialognegmatch.h"

DialogNegMatch::DialogNegMatch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNegMatch)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(this, SIGNAL(runHashDeep(QStringList,QString)), this->parent(), SLOT(run_hashdeep(QStringList,QString)));
}

DialogNegMatch::~DialogNegMatch()
{
    delete ui;
}

void DialogNegMatch::on_pushButtonDir_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditPath->setText(
                QFileDialog::getExistingDirectory
                    (this, tr("Select Directory to Hash"),
                     settings.value("workPlace").toString(), QFileDialog::ShowDirsOnly));
}

void DialogNegMatch::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogNegMatch::on_pushButtonLoadFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogNegMatch::on_pushButtonSaveFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt)")));
}

void DialogNegMatch::on_buttonBox_accepted()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    settings.setValue("workPlace", ui->lineEditPath->text());
    settings.setValue("dataPlace", ui->lineEditSaveFile->text());

    QStringList command;
    bool error = false;

    if (ui->checkRecusive->isChecked() == true) {
        command << "-r";
    }
    if (ui->checkRelPath->isChecked() == true) {
        command << "-l";
    }

    command << "-X";

    command << "-k";

    if (ui->lineEditLoadFile->text() == "") {
        error = true;
    } else {
        command << ui->lineEditLoadFile->text();
    }

    if (ui->lineEditPath->text() == "") {
        error = true;
    } else {
        command << ui->lineEditPath->text();
    }

    if (ui->lineEditSaveFile->text() == "") {
        error = true;
    }

    if (error == false) {
        emit runHashDeep(command, ui->lineEditSaveFile->text());
    }
}
