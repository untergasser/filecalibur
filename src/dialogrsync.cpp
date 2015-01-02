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

#include "dialogrsync.h"
#include "ui_dialogrsync.h"

DialogRsync::DialogRsync(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRsync)
{
    ui->setupUi(this);
}

DialogRsync::~DialogRsync()
{
    delete ui;
}

void DialogRsync::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogRsync::on_pushButtonDirSource_clicked()
{
    ui->lineEditPathSource->setText(
                QFileDialog::getExistingDirectory
                    (this, tr("Select Source Directory"), ".", QFileDialog::ShowDirsOnly));
}

void DialogRsync::on_pushButtonDirTarget_clicked()
{
    ui->lineEditPathTarget->setText(
                QFileDialog::getExistingDirectory
                    (this, tr("Select Target Directory"), ".", QFileDialog::ShowDirsOnly));
}


void DialogRsync::on_buttonBox_accepted()
{
    if (ui->lineEditPathSource->text().isEmpty() || ui->lineEditPathTarget->text().isEmpty()) {
        return;
    }

    QStringList command;
    QString source;
    QString target;
    QString source_out;
    QString target_out;

    bool err = false;

    command << "-rtv";

    command << "--chmod=ugo=rwX";

    if (ui->checkDelete->isChecked() == true) {
        command << "--delete";
    }
    if (ui->checkNoSuper->isChecked() == true) {
        command << "--no-super";
    }


    if (ui->lineEditPathSource->text() == "") {
        err = true;
    }
    if (ui->lineEditPathTarget->text() == "") {
        err = true;
    }
    if (ui->lineEditPathTarget->text() == ui->lineEditPathSource->text()) {
        err = true;
    }
    source = ui->lineEditPathSource->text();
    target = ui->lineEditPathTarget->text();

    source_out = "/cygdrive/";
    source_out.append(source.at(0));
    source_out.append("/");
    source_out.append(source.right(source.count() - 3));
    source_out.append("/");
    source_out.replace("\\", "/");

    target_out = "/cygdrive/";
    target_out.append(target.at(0));
    target_out.append("/");
    target_out.append(target.right(target.count() - 3));
    target_out.replace("\\", "/");

    command << source_out;
    command << target_out;

    if (err == false) {
        DialogRunRsync *runRsync = new DialogRunRsync();
        runRsync->setErrDB(error);
        runRsync->setCommand(command);
        runRsync->show();
        runRsync->runRsync();
    }
}
