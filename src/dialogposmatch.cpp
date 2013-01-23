#include "dialogposmatch.h"
#include "ui_dialogposmatch.h"

DialogPosMatch::DialogPosMatch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPosMatch)
{
    ui->setupUi(this);

    connect(this, SIGNAL(runHashDeep(QStringList,QString)), this->parent(), SLOT(run_hashdeep(QStringList,QString)));
}

DialogPosMatch::~DialogPosMatch()
{
    delete ui;
}

void DialogPosMatch::on_pushButtonDir_clicked()
{
    ui->lineEditPath->setText(
                QFileDialog::getExistingDirectory
                    (this, tr("Select Directory to Hash"), ".", QFileDialog::ShowDirsOnly));
}

void DialogPosMatch::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogPosMatch::on_pushButtonLoadFile_clicked()
{
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"), ".", tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogPosMatch::on_pushButtonSaveFile_clicked()
{
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"), ".", tr("Text Files (*.txt)")));
}

void DialogPosMatch::on_buttonBox_accepted()
{
    QStringList command;
    bool error = false;

    if (ui->checkRecusive->isChecked() == true) {
        command << "-r";
    }
    if (ui->checkRelPath->isChecked() == true) {
        command << "-l";
    }

    command << "-M";

    command << "-k";

    if (ui->lineEditLoadFile->text() == "") {
        error = true;
    } else {
        command << ui->lineEditLoadFile->text();
    }

    if (ui->lineEditPath->text() == "") {
        error = true;
    } else {
        command << ui->lineEditPath->text();
    }

    if (ui->lineEditSaveFile->text() == "") {
        error = true;
    }

    if (error == false) {
        emit runHashDeep(command, ui->lineEditSaveFile->text());
    }
}
