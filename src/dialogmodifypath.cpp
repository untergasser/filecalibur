#include "dialogmodifypath.h"
#include "ui_dialogmodifypath.h"

DialogModifyPath::DialogModifyPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModifyPath)
{
    ui->setupUi(this);

    connect(this, SIGNAL(openResults(QString)), this->parent(), SLOT(updateTable(QString)));
}

DialogModifyPath::~DialogModifyPath()
{
    delete ui;
}


void DialogModifyPath::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogModifyPath::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogModifyPath::on_pushButtonLoadFile_clicked()
{
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"), ".", tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogModifyPath::on_pushButtonSaveFile_clicked()
{
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"), ".", tr("Text Files (*.txt)")));
}

void DialogModifyPath::on_buttonBox_accepted()
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
                QString resStr = "";
                int pos = 0;
                for (int i = 1; i < toPathCols; i++){
                    pos = linStr.indexOf(",", pos + 1);
                }
                pos++;

                resStr.append(linStr.left(pos));

                resStr.append(ui->lineEditTextAdd->text());

                rightStr.append(linStr.right((linStr.length() - pos)));
                if (rightStr.startsWith(delStr) == true) {
                    rightStr.remove(0, delStr.length());
                } else {
                    error->newErr(tr("Path Modification was unabe to remove \""));
                    error->addLast(delStr);
                    error->addLast(tr("\" at: "));
                    error->addLast(rightStr);
                }

                if (ui->rB_back_for->isChecked() == true) {
                    rightStr.replace(QString("\\"),QString("/"));
                }
                if (ui->rb_for_back->isChecked() == true) {
                    rightStr.replace(QString("/"),QString("\\"));
                }

                resStr.append(rightStr);
                //resStr.append("\n");
                sFile.write(resStr.toLocal8Bit());
            }
            sFile.close();
        }
        lFile.close();
    }
    error->checkForErrors();
    emit openResults(ui->lineEditSaveFile->text());
    return;
}

