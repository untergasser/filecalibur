#include "dialogdeletefiles.h"
#include "ui_dialogdeletefiles.h"

DialogDeleteFiles::DialogDeleteFiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDeleteFiles)
{
    ui->setupUi(this);
}

DialogDeleteFiles::~DialogDeleteFiles()
{
    delete ui;
}

void DialogDeleteFiles::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogDeleteFiles::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogDeleteFiles::on_pushButtonLoadFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogDeleteFiles::on_pushButtonDir_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditPath->setText(
                QFileDialog::getExistingDirectory
                    (this, tr("Select Directory to Hash"),
                     settings.value("workPlace").toString(), QFileDialog::ShowDirsOnly));
}

void DialogDeleteFiles::on_pushButtonSaveFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt)")));
}

void DialogDeleteFiles::on_buttonBox_accepted()
{
    int toPathCols = 0;
    bool saveLog = false;

    QFile lFile(ui->lineEditLoadFile->text());
    QFile sFile(ui->lineEditSaveFile->text());

    QSettings settings("A. Untergasser", "Filecalibur");
    settings.setValue("workPlace", ui->lineEditPath->text());

    if (!lFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        error->newErr(tr("Delete Files: Error opening INPUT file: "));
        error->addLast(ui->lineEditLoadFile->text());
    } else {
        if (ui->lineEditSaveFile->text().isEmpty() == false) {
            if (!sFile.open(QIODevice::WriteOnly | QIODevice::Text)){
                error->newErr(tr("Delete Files: Error opening OUTPUT file: "));
                error->addLast(ui->lineEditSaveFile->text());
            } else {
                settings.setValue("dataPlace", ui->lineEditSaveFile->text());
                saveLog = true;
            }
        }
        if (!lFile.atEnd()) {
            lFile.readLine();
        }
        if (!lFile.atEnd()) {
            QByteArray line = lFile.readLine();
            toPathCols = line.count(",") + 1;
        }
        while (!lFile.atEnd()) {
            QByteArray line = lFile.readLine();
            if ((line.at(0) == '#') or (line.at(0) == '%')) {
                continue;
            }
            QString linStr = QString::fromLocal8Bit(line);
            QString authDir = ui->lineEditPath->text();
            QString fileName = "";
            int pos = 0;
            for (int i = 1; i < toPathCols; i++){
                pos = linStr.indexOf(",", pos + 1);
            }
            pos++;

            fileName.append(linStr.right((linStr.length() - pos)));

            if (fileName.startsWith(authDir) == false) {
                error->newErr(tr("Delete Files: file outside authorized folder: "));
                error->addLast(fileName);
                continue;
            }

            QString trimFileName = fileName.trimmed();

            QFile fileToDel(trimFileName.toLocal8Bit());

            if (fileToDel.remove() == true) {
                if (saveLog == true) {
                    fileName.prepend("Deleted - ");
                    sFile.write(fileName.toLocal8Bit());
                }
            } else {
                if (saveLog == true) {
                    error->newErr(tr("Delete Files: Error deleting file: "));
                    error->addLast(fileName);
                    error->addLast(fileToDel.errorString());

                    fileName.prepend("Error Deleting - ");
                    sFile.write(fileName.toLocal8Bit());
                }
            }
        }
        if (saveLog == true) {
            sFile.close();
        }
        lFile.close();
    }
    error->checkForErrors();
    return;
}

