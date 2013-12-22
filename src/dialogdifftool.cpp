#include "dialogdifftool.h"
#include "ui_dialogdifftool.h"

DialogDiffTool::DialogDiffTool(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDiffTool)
{
    ui->setupUi(this);

    connect(&diff_bin, SIGNAL(readyReadStandardError()), this, SLOT(diffUpdateError()));
    connect(&diff_bin, SIGNAL(error(QProcess::ProcessError)), this, SLOT(diffError(QProcess::ProcessError)));
}

DialogDiffTool::~DialogDiffTool()
{
    delete ui;
}

void DialogDiffTool::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogDiffTool::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogDiffTool::on_pushButtonLoadFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogDiffTool::on_pushButtonLoadFile_2_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditLoadFile_2->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogDiffTool::on_buttonBox_accepted()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    settings.setValue("dataPlace", ui->lineEditLoadFile->text());

    QString diff_binPath = settings.value("diff").toString();

    command << ui->lineEditLoadFile->text();
    command << ui->lineEditLoadFile_2->text();

    diff_bin.start(diff_binPath, command);
    diff_bin.closeWriteChannel();

    return;
}

void DialogDiffTool::diffUpdateError()
{
    QByteArray newData = diff_bin.readAllStandardError();
    error->newErr(QString::fromLocal8Bit(newData));
    error->checkForErrors();
}

void DialogDiffTool::diffError(QProcess::ProcessError err)
{
    if(err == QProcess::FailedToStart) {
        error->newErr(tr("Diff Binary not found"));
        error->checkForErrors();
    }
}
