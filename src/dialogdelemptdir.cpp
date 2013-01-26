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
    ui->lineEditPath->setText(
                QFileDialog::getExistingDirectory
                    (this, tr("Select Directory to Hash"), ".", QFileDialog::ShowDirsOnly));
}

void DialogDelEmptDir::on_pushButtonSaveFile_clicked()
{
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"), ".", tr("Text Files (*.txt)")));
}

void DialogDelEmptDir::on_buttonBox_accepted()
{
    QFile sFile(ui->lineEditSaveFile->text());
    bool saveLog = false;
    if (ui->lineEditSaveFile->text().isEmpty() == false) {
        if (!sFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            error->newErr(tr("Delete Files: Error opening OUTPUT file: "));
            error->addLast(ui->lineEditSaveFile->text());
        } else {
            saveLog = true;
        }
    }






    if (saveLog == true) {
        sFile.close();
    }
    error->checkForErrors();
    return;
}

