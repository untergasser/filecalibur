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


