#include "dialogrunrsync.h"
#include "ui_dialogrunrsync.h"

DialogRunRsync::DialogRunRsync(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRunRsync)
{
    ui->setupUi(this);

    rsync_running = false;

    QSettings settings("A. Untergasser", "Filecalibur");


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
    QSettings settings("A. Untergasser", "Filecalibur");
    QString rsync_binPath = settings.value("rsync").toString();

    ui->plainTextEdit->appendPlainText("Hallo");

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
