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

#include "dialogrunrsync.h"
#include "ui_dialogrunrsync.h"

DialogRunRsync::DialogRunRsync(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRunRsync)
{
    ui->setupUi(this);
    rsync_running = false;
    connect(&rsync_bin, SIGNAL(readyReadStandardOutput()), this, SLOT(rsyncUpdateText()));
    connect(&rsync_bin, SIGNAL(readyReadStandardError()), this, SLOT(rsyncUpdateError()));
    connect(&rsync_bin, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(rsyncFinished(int,QProcess::ExitStatus)));
    connect(&rsync_bin, SIGNAL(error(QProcess::ProcessError)), this, SLOT(rsyncError(QProcess::ProcessError)));
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(killRsync()));
}

DialogRunRsync::~DialogRunRsync()
{
    delete ui;
}

void DialogRunRsync::setCommand(QStringList com)
{
    command = com;
}

void DialogRunRsync::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogRunRsync::runRsync()
{
#ifdef Q_OS_WIN
    QString rsync_binPath = "robocopy";


#else
    QString rsync_binPath = "rsync";
#endif

    ui->plainTextEdit->appendPlainText("Command: ");
    ui->plainTextEdit->appendPlainText(rsync_binPath);
    ui->plainTextEdit->appendPlainText(" ");
    ui->plainTextEdit->appendPlainText(command.join(" "));

    rsync_running = true;
    rsync_bin.start(rsync_binPath, command);
    rsync_bin.closeWriteChannel();
}

void DialogRunRsync::killRsync()
{
    if (rsync_running == true){
        rsync_bin.kill();
    }
}

void DialogRunRsync::rsyncUpdateError()
{
    QByteArray newData = rsync_bin.readAllStandardError();
    ErrorMessage.append(QString::fromLocal8Bit(newData));
}

void DialogRunRsync::rsyncUpdateText()
{
    QByteArray newData = rsync_bin.readAllStandardOutput();
    ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit(newData));
}

void DialogRunRsync::rsyncFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::CrashExit) {
        ErrorMessage.append(tr("rsync crashed"));
    } else if (exitCode != 0) {
        ErrorMessage.append(tr("rsync terminated in an unusual way"));
    }
    rsync_running = false;
    ui->pushButton->setText("Close Window");
    error->checkForErrors();
}

void DialogRunRsync::rsyncError(QProcess::ProcessError error)
{
    if(error == QProcess::FailedToStart) {
        ErrorMessage.append(tr("rsync Binary not found"));
        rsync_running = false;
        ui->pushButton->setText("Close Window");
    }
}
