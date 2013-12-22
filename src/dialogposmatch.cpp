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
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditPath->setText(
                QFileDialog::getExistingDirectory
                    (this, tr("Select Directory to Hash"),
                     settings.value("workPlace").toString(), QFileDialog::ShowDirsOnly));
}

void DialogPosMatch::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogPosMatch::on_pushButtonLoadFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogPosMatch::on_pushButtonSaveFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt)")));
}

void DialogPosMatch::on_buttonBox_accepted()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    settings.setValue("workPlace", ui->lineEditPath->text());
    settings.setValue("dataPlace", ui->lineEditSaveFile->text());

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
