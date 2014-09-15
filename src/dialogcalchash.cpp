#include "dialogcalchash.h"
#include "ui_dialogcalchash.h"


DialogCalcHash::DialogCalcHash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCalcHash)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(this, SIGNAL(runHashDeep(QStringList,QString)), this->parent(), SLOT(run_hashdeep(QStringList,QString)));
}

DialogCalcHash::~DialogCalcHash()
{
    delete ui;
}

void DialogCalcHash::on_pushButtonDir_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditPath->setText(QFileDialog::getExistingDirectory
            (this, tr("Select Directory to Hash"),
             settings.value("workPlace").toString(), QFileDialog::ShowDirsOnly));
}

void DialogCalcHash::on_pushButtonSaveFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditSaveFile->setText(QFileDialog::getSaveFileName
            (this, tr("Select a new File"),
             settings.value("dataPlace").toString(), tr("Text Files (*.txt)")));
}

void DialogCalcHash::on_buttonBox_accepted()
{
    QStringList command;
    QString hashCom;
    QSettings settings("A. Untergasser", "Filecalibur");

    bool error = false;
    bool HashUsed = false;

    if (ui->checkRecusive->isChecked() == true) {
        command << "-r";
    }
    if (ui->checkRelPath->isChecked() == true) {
        command << "-l";
    }

    command << "-c";
    hashCom = "";

    if (ui->checkMD5->isChecked() == true) {
        hashCom.append("md5,");
        HashUsed = true;
    }
    if (ui->checkSHA1->isChecked() == true) {
        hashCom.append("sha1,");
        HashUsed = true;
    }
    if (ui->checkSHA256->isChecked() == true) {
        hashCom.append("sha256,");
        HashUsed = true;
    }
    if (ui->checkTIGER->isChecked() == true) {
        hashCom.append("tiger,");
        HashUsed = true;
    }
    if (ui->checkWHIRLPOOL->isChecked() == true) {
        hashCom.append("whirlpool,");
        HashUsed = true;
    }

    if (HashUsed == true) {
        hashCom.chop(1);
        command << hashCom;
    } else {
        error = true;
    }

    if (ui->lineEditPath->text() == "") {
        error = true;
    } else {
        settings.setValue("workPlace", ui->lineEditPath->text());
        command << ui->lineEditPath->text();
    }

    if (ui->lineEditSaveFile->text() == "") {
        error = true;
    } else {
        settings.setValue("dataPlace", ui->lineEditSaveFile->text());
    }

    if (error == false) {
        emit runHashDeep(command, ui->lineEditSaveFile->text());
    }
}
