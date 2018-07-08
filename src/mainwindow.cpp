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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    programVersion = "Version 0.8.0 BETA";

    ui->setupUi(this);

    hashdeep_saveFile  = "";
    table_used         = false;

    error = new DialogErrorMessage(this);

    connect(&hashdeep_bin, SIGNAL(readyReadStandardError()), this, SLOT(hashDeepUpdateError()));
    connect(&hashdeep_bin, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(hashDeepFinished(int,QProcess::ExitStatus)));
    connect(&hashdeep_bin, SIGNAL(error(QProcess::ProcessError)), this, SLOT(hashDeepError(QProcess::ProcessError)));

    QSettings settings("A. Untergasser", "Filecalibur");
    int setup = settings.value("Initial Setup").toInt();
    if (setup != 1) {
        settings.setValue("Initial Setup", 1);
        on_actionSettings_triggered();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSettings_triggered()
{
    optionen = new DialogOptionen(this);
    optionen->show();
}

void MainWindow::run_hashdeep(QStringList command, QString saFi)
{
    hashdeep_saveFile = saFi;
    QSettings settings("A. Untergasser", "Filecalibur");
    QString hashDeep_binPath = settings.value("hashdeep").toString();

    hashdeep_bin.setStandardOutputFile(hashdeep_saveFile, QIODevice::Truncate);
    hashdeep_bin.start(hashDeep_binPath, command);
    hashdeep_bin.closeWriteChannel();

    hashRun = new DialogRunHasDeep(this);
    hashRun->show();
}

void MainWindow::killHashDeep()
{
    hashdeep_bin.kill();
}

void MainWindow::hashDeepUpdateError()
{
    QByteArray newData = hashdeep_bin.readAllStandardError();
    error->newErr(tr("HashDeep created error:"));
    error->addLast(QString::fromLocal8Bit(newData));
}

void MainWindow::hashDeepFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::CrashExit) {
        error->newErr(tr("HashDeep crashed"));
    } else if (exitCode != 0) {
        error->newErr(tr("HashDeep terminated in an unusual way"));
    }
    hashRun->reject();
    updateTable();
    error->checkForErrors();
}

void MainWindow::hashDeepError(QProcess::ProcessError err)
{
    if(err == QProcess::FailedToStart) {
        error->newErr(tr("Hashdeep Binary not found"));
    }
}

void MainWindow::updateTable(QString fileSt)
{
    readFileToMem(fileSt);
    table_model.setup(table_cols, table_headers, &table_content);
    ui->tableView->setModel(&table_model);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::updateTable()
{
    readFileToMem();
    table_model.setup(table_cols, table_headers, &table_content);
    ui->tableView->setModel(&table_model);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::readFileToMem() {
    readFileToMem(hashdeep_saveFile);
}


void MainWindow::readFileToMem(QString fileSt)
{
    if (table_used == true){
        MainWindow *newWin = new MainWindow();
        newWin->setFile(fileSt);
        newWin->updateTable();
        newWin->show();
        return;
    }
    hashdeep_saveFile = fileSt;
    table_cols = 0;
    QString lineString;
    QString topText;
    QString title;
    QFile file(hashdeep_saveFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        error->newErr(tr("Error opening results file: "));
        error->addLast(hashdeep_saveFile);
    } else {
        if (!file.atEnd()) {
            QByteArray line = file.readLine();
            topText.append(QString::fromLocal8Bit(line));
        }
        if (!file.atEnd()) {
            QByteArray line = file.readLine();
            topText.append(QString::fromLocal8Bit(line));
            table_cols = line.count(",") + 1;
            line.remove(0,5);
            lineString = QString::fromLocal8Bit(line);
            table_headers = lineString.split(",");
            table_headers.removeLast();
            table_headers.prepend("filename");
        }
        while (!file.atEnd()) {
            QByteArray line = file.readLine();

            if ((line.at(0) == '#') or (line.at(0) == '%')) {
                topText.append(QString::fromLocal8Bit(line));
                continue;
            }
            table_content << QString::fromLocal8Bit(line);
        }
        file.close();
        table_used = true;
        ui->plainTextEdit->appendPlainText(topText);
    }

    title = fileSt;
    title.append(" - ");
    title.append(QString("%1").arg(table_content.count()));
    title.append(tr(" files"));
    setWindowTitle(title);

    error->checkForErrors();
}

void MainWindow::setFile(QString file_String)
{
    hashdeep_saveFile = file_String;
}


void MainWindow::on_actionOpen_triggered()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    hashdeep_saveFile = settings.value("dataPlace").toString();

    hashdeep_saveFile = QFileDialog::getOpenFileName(this, tr("Select a File"), hashdeep_saveFile, tr("Text Files (*.txt);;All Files (*.*)"));
    if (hashdeep_saveFile != 0) {
        settings.setValue("dataPlace", hashdeep_saveFile);
        updateTable();
    }
}

void MainWindow::on_actionCalculate_Hashes_triggered()
{
    hashIt = new DialogCalcHash(this);
    hashIt->show();
}

void MainWindow::on_actionSync_Directories_triggered()
{
    DialogRsync *rsync = new DialogRsync();
    rsync->setErrDB(error);
    rsync->show();
}

void MainWindow::on_actionModify_Path_triggered()
{
    modifyPath = new DialogModifyPath(this);
    modifyPath->setErrDB(error);
    modifyPath->setLoadFile(hashdeep_saveFile);
    modifyPath->show();
}

void MainWindow::on_actionRemove_Path_triggered()
{
    removePath = new DialogRemovePath(this);
    removePath->setErrDB(error);
    removePath->setLoadFile(hashdeep_saveFile);
    removePath->show();
}

void MainWindow::on_actionExtract_Path_triggered()
{
    extractPath = new DialogExtractPath(this);
    extractPath->setErrDB(error);
    extractPath->setLoadFile(hashdeep_saveFile);
    extractPath->show();
}

void MainWindow::on_actionJoin_Files_triggered()
{
    joinFiles = new DialogJoinFiles(this);
    joinFiles->setErrDB(error);
    joinFiles->setLoadFile(hashdeep_saveFile);
    joinFiles->show();
}

void MainWindow::on_actionPositive_Hashing_triggered()
{
    positiveHashing = new DialogPositiveHashing(this);
    positiveHashing->setErrDB(error);
    positiveHashing->setLoadFile(hashdeep_saveFile);
    positiveHashing->show();
}

void MainWindow::on_actionNegative_Hashing_triggered()
{
    negativeHashing = new DialogNegativeHashing(this);
    negativeHashing->setErrDB(error);
    negativeHashing->setLoadFile(hashdeep_saveFile);
    negativeHashing->show();
}


void MainWindow::on_actionFind_Duplicates_triggered()
{
    findDuplicates = new DialogFindDuplicates(this);
    findDuplicates->setErrDB(error);
    findDuplicates->setLoadFile(hashdeep_saveFile);
    findDuplicates->show();
}


void MainWindow::on_actionFind_Long_Names_triggered()
{
    findLongName = new DialogFindLongName(this);
    findLongName->setErrDB(error);
    findLongName->setLoadFile(hashdeep_saveFile);
    findLongName->show();
}


void MainWindow::on_actionCompare_Files_triggered()
{
    diffTool = new DialogDiffTool(this);
    diffTool->setErrDB(error);
    diffTool->setLoadFile(hashdeep_saveFile);
    diffTool->show();
}

void MainWindow::on_actionDelete_Files_from_List_triggered()
{
    deleteFiles = new DialogDeleteFiles(this);
    deleteFiles->setErrDB(error);
    deleteFiles->setLoadFile(hashdeep_saveFile);
    deleteFiles->show();
}

void MainWindow::on_actionDelete_Empty_Directories_triggered()
{
    delEmptDir = new DialogDelEmptDir(this);
    delEmptDir->setErrDB(error);
    delEmptDir->show();
}

void MainWindow::on_actionSupport_triggered()
{
    QUrl urlLink("http://sourceforge.net/projects/filecalibur/files/");
    QDesktopServices::openUrl(urlLink);
}

void MainWindow::on_actionHashdeep_triggered()
{
    QUrl urlLink("http://md5deep.sourceforge.net/");
    QDesktopServices::openUrl(urlLink);
}

void MainWindow::on_actionRsync_triggered()
{
    QUrl urlLink("http://rsync.samba.org/");
    QDesktopServices::openUrl(urlLink);
}

void MainWindow::on_actionWinmerge_triggered()
{
    QUrl urlLink("http://winmerge.org/");
    QDesktopServices::openUrl(urlLink);
}

void MainWindow::on_actionFilecalibur_at_Souceforge_triggered()
{
    QUrl urlLink("https://github.com/untergasser/filecalibur/");
    QDesktopServices::openUrl(urlLink);
}

void MainWindow::on_actionTutorials_triggered()
{
    if (QLocale::system().name().startsWith("de") == true) {
        QUrl urlLink("http://www.filecalibur.de/");
        QDesktopServices::openUrl(urlLink);
    } else {
        QUrl urlLink("http://www.filecalibur.com");
        QDesktopServices::openUrl(urlLink);
    }
}

void MainWindow::on_actionManual_triggered()
{
    DialogManual *manual = new DialogManual(this);
    QString text = "";
    if (QLocale::system().name().startsWith("de") == true) {
        QFile file(":/manual_de.htm");
        file.open(QIODevice::ReadOnly);
        text = QString::fromUtf8(file.readAll());
        file.close();
    } else {
        QFile file(":/manual_en.htm");
        file.open(QIODevice::ReadOnly);
        text = QString::fromUtf8(file.readAll());
        file.close();
    }
    manual->setManual(text);
    manual->show();
}

void MainWindow::on_actionAbout_triggered()
{
    DialogAbout *about = new DialogAbout(programVersion, this);
    QFile file(":/license.txt");
    file.open(QIODevice::ReadOnly);
    QString text = QString::fromUtf8(file.readAll());
    file.close();
    about->setLicense(text);
    about->show();
}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (index.column() != 0) {
        return;
    }
    QString filePath = table_model.data(index, Qt::DisplayRole).toString();
    filePath.chop(1);
    QFileInfo checkFile(filePath);
    if (checkFile.exists() && checkFile.isFile()) {
        QString urlFile = "file:///";
        urlFile.append(checkFile.canonicalFilePath());
        QDesktopServices::openUrl(QUrl(urlFile, QUrl::TolerantMode));
    }
}
