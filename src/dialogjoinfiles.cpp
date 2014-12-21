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

#include "dialogjoinfiles.h"
#include "ui_dialogjoinfiles.h"

DialogJoinFiles::DialogJoinFiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogJoinFiles)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(this, SIGNAL(openResults(QString)), this->parent(), SLOT(updateTable(QString)));
}

DialogJoinFiles::~DialogJoinFiles()
{
    delete ui;
}

void DialogJoinFiles::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogJoinFiles::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogJoinFiles::on_pushButtonLoadFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogJoinFiles::on_pushButtonLoadFile_2_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditLoadFile_2->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogJoinFiles::on_pushButtonSaveFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt)")));
}

void DialogJoinFiles::on_buttonBox_accepted()
{
    if (ui->lineEditLoadFile->text().isEmpty() ||
        ui->lineEditLoadFile_2->text().isEmpty() || ui->lineEditSaveFile->text().isEmpty()) {
        return;
    }

    QFile lFile(ui->lineEditLoadFile->text());
    QFile lFile_2(ui->lineEditLoadFile_2->text());
    QFile sFile(ui->lineEditSaveFile->text());
    if (!lFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        error->newErr(tr("Join Files created Error opening FIRST INPUT file: "));
        error->addLast(ui->lineEditLoadFile->text());
    } else {
        if (!lFile_2.open(QIODevice::ReadOnly | QIODevice::Text)){
            error->newErr(tr("Join Files created Error opening SECOND INPUT file: "));
            error->addLast(ui->lineEditLoadFile_2->text());
        } else {
            if (!sFile.open(QIODevice::WriteOnly | QIODevice::Text)){
                error->newErr(tr("Join Files created Error opening OUTPUT file: "));
                error->addLast(ui->lineEditSaveFile->text());
            } else {
                QSettings settings("A. Untergasser", "Filecalibur");
                settings.setValue("dataPlace", ui->lineEditSaveFile->text());

                QByteArray line;
                QByteArray line_2;
                if (!lFile.atEnd()) {
                    // Copy over the first line;
                    sFile.write(lFile.readLine());
                }
                if (!lFile.atEnd()) {
                    line = lFile.readLine();
                    sFile.write(line);
                }
                if (!lFile_2.atEnd()) {
                    // Trash first line of File 2;
                    lFile_2.readLine();
                }
                if (!lFile_2.atEnd()) {
                    // Required so both files have identical hases;
                    line_2 = lFile_2.readLine();
                    QString linStr = QString::fromLocal8Bit(line);
                    QString linStr_2 = QString::fromLocal8Bit(line_2);
                    if (linStr != linStr_2) {
                        error->newErr(tr("Join Files can not join files with different hashes."));
                        error->checkForErrors();
                        sFile.close();
                        lFile_2.close();
                        lFile.close();
                        return;
                    }

                }
                // Just in case:
                line = lFile.readLine();
                line_2 = lFile_2.readLine();
                if ((line.at(0) == '%') or (line_2.at(0) == '%')) {
                    error->newErr(tr("Join Files detected untypical input files."));
                    error->checkForErrors();
                    sFile.close();
                    lFile_2.close();
                    lFile.close();
                    return;
                }
                sFile.write("## Joined two files:\n");
                bool run = true;
                while ((line.at(0) == '#') and (run == true)) {
                    QString linStr = QString::fromLocal8Bit(line);
                    if (linStr != "## \n") {
                        sFile.write(line);
                    }
                    if (!lFile.atEnd()) {
                        line = lFile.readLine();
                    } else {
                        run = false;
                    }
                }
                run = true;
                while ((line_2.at(0) == '#') and (run == true)) {
                    sFile.write(line_2);
                    if (!lFile_2.atEnd()) {
                        line_2 = lFile_2.readLine();
                    } else {
                        run = false;
                    }
                }

                sFile.write(line);
                while (!lFile.atEnd()) {
                    sFile.write(lFile.readLine());
                }

                sFile.write(line_2);
                while (!lFile_2.atEnd()) {
                    sFile.write(lFile_2.readLine());
                }

                sFile.close();
            }
            lFile_2.close();
        }
        lFile.close();
    }
    error->checkForErrors();
    emit openResults(ui->lineEditSaveFile->text());
    return;
}
