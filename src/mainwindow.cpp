#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hashdeep_saveFile  = "";
    table_used         = false;

    error = new DialogErrorMessage(this);

    connect(&hashdeep_bin, SIGNAL(readyReadStandardError()), this, SLOT(hashDeepUpdateError()));
    connect(&hashdeep_bin, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(hashDeepFinished(int,QProcess::ExitStatus)));
    connect(&hashdeep_bin, SIGNAL(error(QProcess::ProcessError)), this, SLOT(hashDeepError(QProcess::ProcessError)));
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

    QString hashDeep_binPath = "C:\\_progs\\Filecalibur\\build\\debug\\bin\\hashdeep64.exe";

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
    error->checkForErrors();
}

void MainWindow::setFile(QString file_String)
{
    hashdeep_saveFile = file_String;
}


void MainWindow::on_actionOpen_triggered()
{
    hashdeep_saveFile = QFileDialog::getOpenFileName(this, tr("Select a File"), ".", tr("Text Files (*.txt);;All Files (*.*)"));
    if (hashdeep_saveFile != 0) {
        updateTable();
    }
}

void MainWindow::on_actionCalculate_Hashes_triggered()
{
    hashIt = new DialogCalcHash(this);
    hashIt->show();
}

void MainWindow::on_actionPositive_Matching_triggered()
{
    hashPos = new DialogPosMatch(this);
    hashPos->setLoadFile(hashdeep_saveFile);
    hashPos->show();
}


void MainWindow::on_actionNegative_Matching_triggered()
{
    hashNeg = new DialogNegMatch(this);
    hashNeg->setLoadFile(hashdeep_saveFile);
    hashNeg->show();
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

}

void MainWindow::on_actionNegative_Hashing_triggered()
{

}

