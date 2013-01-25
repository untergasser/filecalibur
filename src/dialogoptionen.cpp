#include "dialogoptionen.h"
#include "ui_dialogoptionen.h"

DialogOptionen::DialogOptionen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOptionen)
{
    ui->setupUi(this);

    QSettings settings("A. Untergasser", "Filecalibur");
    QString hashprog = settings.value("hashdeep").toString();
    if (hashprog.isEmpty()) {
        ui->lineEditHashdeep->setText("C:\\_progs\\Filecalibur\\build\\debug\\bin\\hashdeep64.exe");
    } else {
        ui->lineEditHashdeep->setText(hashprog);
    }
    QString syncprog = settings.value("rsync").toString();
    if (syncprog.isEmpty()) {
        ui->lineEditRsync->setText("C:\\_progs\\Filecalibur\\build\\debug\\bin\\rsync.exe");
    } else {
        ui->lineEditRsync->setText(syncprog);
    }
    QString diffprog = settings.value("diff").toString();
    if (diffprog.isEmpty()) {
        ui->lineEditDiff->setText("C:\\Program Files (x86)\\WinMerge\\WinMergeU.exe");
    } else {
        ui->lineEditDiff->setText(diffprog);
    }
}

DialogOptionen::~DialogOptionen()
{
    delete ui;
}

void DialogOptionen::on_pushButtonHashdeep_clicked()
{
    QString hashprog = QFileDialog::getOpenFileName
                    (this, tr("Select an Executables"), ".", tr("Executables (*.exe);;All Files (*.*)"));
    hashprog.replace(QString("/"),QString("\\"));
    ui->lineEditHashdeep->setText(hashprog);
}

void DialogOptionen::on_pushButtonRsync_clicked()
{
    QString syncprog = QFileDialog::getOpenFileName
                    (this, tr("Select an Executables"), ".", tr("Executables (*.exe);;All Files (*.*)"));
    syncprog.replace(QString("/"),QString("\\"));
    ui->lineEditRsync->setText(syncprog);
}

void DialogOptionen::on_pushButtonDiff_clicked()
{
    QString diffprog = QFileDialog::getOpenFileName
                    (this, tr("Select an Executables"), ".", tr("Executables (*.exe);;All Files (*.*)"));
    diffprog.replace(QString("/"),QString("\\"));
    ui->lineEditDiff->setText(diffprog);
}

void DialogOptionen::on_buttonBox_accepted()
{
    QSettings settings("A. Untergasser", "Filecalibur");

    QString hashprog = ui->lineEditHashdeep->text();
    hashprog.replace(QString("/"),QString("\\"));
    settings.setValue("hashdeep", hashprog);

    QString syncprog = ui->lineEditRsync->text();
    syncprog.replace(QString("/"),QString("\\"));
    settings.setValue("rsync", syncprog);

    QString diffprog = ui->lineEditDiff->text();
    diffprog.replace(QString("/"),QString("\\"));
    settings.setValue("diff", diffprog);
}

