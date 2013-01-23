#include "dialogextractpath.h"
#include "ui_dialogextractpath.h"

DialogExtractPath::DialogExtractPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExtractPath)
{
    ui->setupUi(this);

    connect(this, SIGNAL(openResults(QString)), this->parent(), SLOT(updateTable(QString)));
}

DialogExtractPath::~DialogExtractPath()
{
    delete ui;
}

void DialogExtractPath::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogExtractPath::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogExtractPath::on_pushButtonLoadFile_clicked()
{
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"), ".", tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogExtractPath::on_pushButtonSaveFile_clicked()
{
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"), ".", tr("Text Files (*.txt)")));
}

void DialogExtractPath::on_buttonBox_accepted()
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
                if (rightStr.startsWith(delStr) == true) {
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
