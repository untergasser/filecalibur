#include "dialogfindlongname.h"
#include "ui_dialogfindlongname.h"

DialogFindLongName::DialogFindLongName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFindLongName)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(this, SIGNAL(openResults(QString)), this->parent(), SLOT(updateTable(QString)));
}

DialogFindLongName::~DialogFindLongName()
{
    delete ui;
}

void DialogFindLongName::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogFindLongName::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogFindLongName::on_pushButtonLoadFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogFindLongName::on_pushButtonSaveFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt)")));
}

void DialogFindLongName::on_buttonBox_accepted()
{
    if (ui->lineEditLoadFile->text().isEmpty() || ui->lineEditSaveFile->text().isEmpty()) {
        return;
    }

    int maxSize = ui->lineEditCharLim->text().toInt();

    // Now we process the file
    QFile lFile(ui->lineEditLoadFile->text());
    QFile sFile(ui->lineEditSaveFile->text());
    if (!lFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        error->newErr(tr("Find Long Names: Error opening INPUT file: "));
        error->addLast(ui->lineEditLoadFile->text());
    } else {
        if (!sFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            error->newErr(tr("Find Long Names: Error opening OUTPUT file: "));
            error->addLast(ui->lineEditSaveFile->text());
        } else {
            QSettings settings("A. Untergasser", "Filecalibur");
            settings.setValue("dataPlace", ui->lineEditSaveFile->text());

            if (!lFile.atEnd()) {
                QByteArray line = lFile.readLine();
                sFile.write(line);
            }
            if (!lFile.atEnd()) {
                QByteArray line = lFile.readLine();
                sFile.write(line);
            }
            // Compare the content
            while (!lFile.atEnd()) {
                QByteArray line = lFile.readLine();
                if ((line.at(0) == '#') or (line.at(0) == '%')) {
                    sFile.write(line);
                    continue;
                }
                QString linStr = QString::fromLocal8Bit(line);

                // Now add the selected line to the file table
                if (ui->checkBoxPathIncl->isChecked() == false) {
                    int dirLast = linStr.lastIndexOf('/');
                    if (dirLast < linStr.lastIndexOf('\\')) {
                        dirLast = linStr.lastIndexOf('\\');
                    }
                    if (linStr.size() - dirLast > maxSize) {
                        sFile.write(line);
                    }
                } else {
                    if (linStr.size() - linStr.lastIndexOf(',') > maxSize) {
                        sFile.write(line);
                    }
                }
            }
            sFile.close();
        }
        lFile.close();
    }
    error->checkForErrors();
    emit openResults(ui->lineEditSaveFile->text());
    return;
}
