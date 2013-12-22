#include "dialogremovepath.h"
#include "ui_dialogremovepath.h"

DialogRemovePath::DialogRemovePath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRemovePath)
{
    ui->setupUi(this);

    connect(this, SIGNAL(openResults(QString)), this->parent(), SLOT(updateTable(QString)));
}

DialogRemovePath::~DialogRemovePath()
{
    delete ui;
}

void DialogRemovePath::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogRemovePath::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogRemovePath::on_pushButtonLoadFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogRemovePath::on_pushButtonSaveFile_clicked()
{
    QSettings settings("A. Untergasser", "Filecalibur");
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"),
                     settings.value("dataPlace").toString(), tr("Text Files (*.txt)")));
}

void DialogRemovePath::on_buttonBox_accepted()
{
    int toPathCols = 0;

    QFile lFile(ui->lineEditLoadFile->text());
    QFile sFile(ui->lineEditSaveFile->text());
    if (!lFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        error->newErr(tr("Path Modification created Error opening INPUT file: "));
        error->addLast(ui->lineEditLoadFile->text());
    } else {
        if (!sFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            error->newErr(tr("Path Modification created Error opening OUTPUT file: "));
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
                toPathCols = line.count(",") + 1;
                sFile.write(line);
            }
            while (!lFile.atEnd()) {
                QByteArray line = lFile.readLine();
                if ((line.at(0) == '#') or (line.at(0) == '%')) {
                    sFile.write(line);
                    continue;
                }
                QString linStr = QString::fromLocal8Bit(line);
                QString delStr = ui->lineEditTextRemove->text();
                QString rightStr = "";
                int pos = 0;
                for (int i = 1; i < toPathCols; i++){
                    pos = linStr.indexOf(",", pos + 1);
                }
                pos++;
                rightStr.append(linStr.right((linStr.length() - pos)));
                if (rightStr.startsWith(delStr) != true) {
                    sFile.write(line);
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
