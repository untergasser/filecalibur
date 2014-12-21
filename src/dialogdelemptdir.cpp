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

#include "dialogdelemptdir.h"
#include "ui_dialogdelemptdir.h"

DialogDelEmptDir::DialogDelEmptDir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDelEmptDir)
{
    ui->setupUi(this);
}

DialogDelEmptDir::~DialogDelEmptDir()
{
    delete ui;
}

void DialogDelEmptDir::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogDelEmptDir::on_pushButtonDir_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditPath->setText(
                QFileDialog::getExistingDirectory
                    (this, tr("Select Directory"),
                     settings.value("workPlace").toString(), QFileDialog::ShowDirsOnly));
}

void DialogDelEmptDir::on_pushButtonSaveFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt)")));
}

void DialogDelEmptDir::on_buttonBox_accepted()
{
    if (ui->lineEditPath->text().isEmpty()) {
        return;
    }

    QFile sFile(ui->lineEditSaveFile->text());
    bool saveLog = false;

    QSettings settings("A. Untergasser", "Filecalibur");
    settings.setValue("workPlace", ui->lineEditPath->text());

    if (ui->lineEditSaveFile->text().isEmpty() == false) {
        if (!sFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            error->newErr(tr("Delete Empty Dirs: Error opening OUTPUT file: "));
            error->addLast(ui->lineEditSaveFile->text());
        } else {
            settings.setValue("dataPlace", ui->lineEditSaveFile->text());
            saveLog = true;
        }
    }

    // Now we travel through the directories
    travelDirs(ui->lineEditPath->text());

    if (saveLog == true) {
        QString strOut = logData.join("\n");
        sFile.write(strOut.toLocal8Bit());
        sFile.close();
    }
    error->checkForErrors();
    return;
}

void DialogDelEmptDir::travelDirs(QString dirCurr)
{
    QDir current(dirCurr);
    current.setSorting(QDir::Name);
    current.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    // First take care of the subdirectories
    QFileInfoList dirOnly = current.entryInfoList();
    for (int i = 0; i < dirOnly.size(); ++i) {
        QFileInfo fileInfo = dirOnly.at(i);
        travelDirs(fileInfo.absoluteFilePath());
    }

    // Then take care of the folders
    current.setFilter(QDir::Dirs | QDir::Files | QDir::Hidden | QDir::System | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    QFileInfoList completeDir = current.entryInfoList();
    if (completeDir.size() == 0) {
        QString message;

        if (ui->checkBoxSimulate->isChecked() == false) {
            if (current.rmdir(dirCurr) == true) {
                message = "Deleted - ";
                message.append(dirCurr);
                logData << message;
            } else {
                message = "Error Deleting - ";
                message.append(dirCurr);
                logData << message;
                message.prepend("Delete Empty Dirs: ");
                error->newErr(message);
            }
        } else {
            message = "Would Delete - ";
            message.append(dirCurr);
            logData << message;
        }
    }
}


