#include "dialognegmatch.h"
#include "ui_dialognegmatch.h"

DialogNegMatch::DialogNegMatch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNegMatch)
{
    ui->setupUi(this);

    connect(this, SIGNAL(runHashDeep(QStringList,QString)), this->parent(), SLOT(run_hashdeep(QStringList,QString)));
}

DialogNegMatch::~DialogNegMatch()
{
    delete ui;
}

void DialogNegMatch::on_pushButtonDir_clicked()
{
    ui->lineEditPath->setText(
                QFileDialog::getExistingDirectory
                    (this, tr("Select Directory to Hash"), ".", QFileDialog::ShowDirsOnly));
}

void DialogNegMatch::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogNegMatch::on_pushButtonLoadFile_clicked()
{
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"), ".", tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogNegMatch::on_pushButtonSaveFile_clicked()
{
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"), ".", tr("Text Files (*.txt)")));
}

void DialogNegMatch::on_buttonBox_accepted()
{
    QStringList command;
    bool error = false;

    if (ui->checkRecusive->isChecked() == true) {
        command << "-r";
    }
    if (ui->checkRelPath->isChecked() == true) {
        command << "-l";
    }

    command << "-X";

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
