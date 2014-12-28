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

#include "dialogoptionen.h"
#include "ui_dialogoptionen.h"

DialogOptionen::DialogOptionen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOptionen)
{
    ui->setupUi(this);

    QSettings settings("A. Untergasser", "Filecalibur");
    QString hashprog = settings.value("hashdeep").toString();
    if (hashprog.isEmpty()) {
        ui->lineEditHashdeep->setText("C:\\Program Files\\filecalibur\\hashdeep\\hashdeep.exe");
    } else {
        ui->lineEditHashdeep->setText(hashprog);
    }
    QString syncprog = settings.value("rsync").toString();
    if (syncprog.isEmpty()) {
        ui->lineEditRsync->setText("C:\\Program Files\\filecalibur\\rsync\\rsync.exe");
    } else {
        ui->lineEditRsync->setText(syncprog);
    }
    QString diffprog = settings.value("diff").toString();
    if (diffprog.isEmpty()) {
        ui->lineEditDiff->setText("C:\\Program Files\\WinMerge\\WinMergeU.exe");
    } else {
        ui->lineEditDiff->setText(diffprog);
    }
}

DialogOptionen::~DialogOptionen()
{
    delete ui;
}

void DialogOptionen::on_pushButtonHashdeep_clicked()
{
    QString hashprog = QFileDialog::getOpenFileName
                    (this, tr("Select an Executables"),
                     ui->lineEditHashdeep->text(), tr("Executables (*.exe);;All Files (*.*)"));
    hashprog.replace(QString("/"),QString("\\"));
    ui->lineEditHashdeep->setText(hashprog);
}

void DialogOptionen::on_pushButtonRsync_clicked()
{
    QString syncprog = QFileDialog::getOpenFileName
                    (this, tr("Select an Executables"),
                     ui->lineEditRsync->text(), tr("Executables (*.exe);;All Files (*.*)"));
    syncprog.replace(QString("/"),QString("\\"));
    ui->lineEditRsync->setText(syncprog);
}

void DialogOptionen::on_pushButtonDiff_clicked()
{
    QString diffprog = QFileDialog::getOpenFileName
                    (this, tr("Select an Executables"),
                     ui->lineEditDiff->text(), tr("Executables (*.exe);;All Files (*.*)"));
    diffprog.replace(QString("/"),QString("\\"));
    ui->lineEditDiff->setText(diffprog);
}

void DialogOptionen::on_buttonBox_accepted()
{
    QSettings settings("A. Untergasser", "Filecalibur");

    QString hashprog = ui->lineEditHashdeep->text();
    hashprog.replace(QString("/"),QString("\\"));
    settings.setValue("hashdeep", hashprog);

    QString syncprog = ui->lineEditRsync->text();
    syncprog.replace(QString("/"),QString("\\"));
    settings.setValue("rsync", syncprog);

    QString diffprog = ui->lineEditDiff->text();
    diffprog.replace(QString("/"),QString("\\"));
    settings.setValue("diff", diffprog);
}

