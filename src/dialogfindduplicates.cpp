#include "dialogfindduplicates.h"
#include "ui_dialogfindduplicates.h"

DialogFindDuplicates::DialogFindDuplicates(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFindDuplicates)
{
    ui->setupUi(this);

    connect(this, SIGNAL(openResults(QString)), this->parent(), SLOT(updateTable(QString)));
}

DialogFindDuplicates::~DialogFindDuplicates()
{
    delete ui;
}

void DialogFindDuplicates::setErrDB(DialogErrorMessage *err)
{
    error = err;
}

void DialogFindDuplicates::setLoadFile(QString suggestion)
{
    ui->lineEditLoadFile->setText(suggestion);
}

void DialogFindDuplicates::on_pushButtonLoadFile_clicked()
{
    ui->lineEditLoadFile->setText(
                QFileDialog::getOpenFileName
                    (this, tr("Select a File"), ".", tr("Text Files (*.txt);;All Files (*.*)")));
}

void DialogFindDuplicates::on_pushButtonSaveFile_clicked()
{
    ui->lineEditSaveFile->setText(
                QFileDialog::getSaveFileName
                    (this, tr("Select a new File"), ".", tr("Text Files (*.txt)")));
}

void DialogFindDuplicates::on_buttonBox_accepted()
{
    QHash<QString, int> hash;
    int comma = 0;
    bool run = true;

    QString hashToUse = "XXX";
    if (ui->radioMD5->isChecked()) {
        hashToUse = "md5";
    }
    if (ui->radioSHA1->isChecked()) {
        hashToUse = "sha1";
    }
    if (ui->radioSHA256->isChecked()) {
        hashToUse = "sha256";
    }
    if (ui->radioTIGER->isChecked()) {
        hashToUse = "tiger";
    }
    if (ui->radioWHIRLPOOL->isChecked()) {
        hashToUse = "whirlpool";
    }

    QFile hashFile(ui->lineEditLoadFile->text());
    if (!hashFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        error->newErr(tr("Find Duplicates: Error opening file: "));
        error->addLast(ui->lineEditLoadFile->text());
        error->checkForErrors();
        return;
    } else {
        if (!hashFile.atEnd()) {
            hashFile.readLine();
        }
        if (!hashFile.atEnd()) {
            QByteArray line = hashFile.readLine();
            QString linStr = QString::fromLocal8Bit(line);
            if (linStr.contains(hashToUse) == false) {
                error->newErr(tr("Find Duplicates: Selected HASH not existent in file: "));
                error->addLast(ui->lineEditLoadFile->text());
                hashFile.close();
                error->checkForErrors();
                return;
            }
            QString Result;
            // Find which column contains our hash
            int pos = 0;
            for (int i = 1;((i < 10) and (run == true)); i++){
                pos = linStr.indexOf(",", pos + 1);
                Result = linStr.right(linStr.length() - pos - 1);
                if (Result.startsWith(hashToUse) == true ) {
                    comma = i;
                    run = false;
                }
            }
        }
        // Read the file to the hash
        while (!hashFile.atEnd()) {
            QByteArray line = hashFile.readLine();
            if ((line.at(0) == '#') or (line.at(0) == '%')) {
                continue;
            }
            QString linStr = QString::fromLocal8Bit(line);

            int leftPos = 0;
            int rightPos = 0;
            int pos = 0;
            for (int i = 0; i <= comma; i++){
                pos = linStr.indexOf(",", pos + 1);
                if (i == (comma-1)) {
                    leftPos = pos;
                }
                if (i == comma) {
                    rightPos = pos;
                }
            }
            // Now add the selected hash value to the hash table an count the times
            QString keyVal = linStr.mid(leftPos + 1, rightPos - leftPos - 1);
            hash.insert(keyVal, 1 + hash[keyVal]);
        }
        hashFile.close();
    }

    // Now we really process the file
    QFile lFile(ui->lineEditLoadFile->text());
    QFile sFile(ui->lineEditSaveFile->text());
    if (!lFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        error->newErr(tr("Find Duplicates: Error opening INPUT file: "));
        error->addLast(ui->lineEditLoadFile->text());
    } else {
        if (!sFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            error->newErr(tr("Find Duplicates: Error opening OUTPUT file: "));
            error->addLast(ui->lineEditSaveFile->text());
        } else {
            if (!lFile.atEnd()) {
                QByteArray line = lFile.readLine();
                sFile.write(line);
            }
            if (!lFile.atEnd()) {
                QByteArray line = lFile.readLine();
                sFile.write(line);
                QString linStr = QString::fromLocal8Bit(line);
                if (linStr.contains(hashToUse) == false) {
                    error->newErr(tr("Find Duplicates: Selected HASH not existent in INPUT file: "));
                    error->addLast(ui->lineEditLoadFile->text());
                    sFile.close();
                    lFile.close();
                    error->checkForErrors();
                    return;
                }
                QString Result;
                // Find which column contains our hash
                int pos = 0;
                for (int i = 1;((i < 10) and (run == true)); i++){
                    pos = linStr.indexOf(",", pos + 1);
                    Result = linStr.right(linStr.length() - pos - 1);
                    if (Result.startsWith(hashToUse) == true ) {
                        comma = i;
                        run = false;
                    }
                }
            }
            // Compare the content
            int result;
            while (!lFile.atEnd()) {
                QByteArray line = lFile.readLine();
                if ((line.at(0) == '#') or (line.at(0) == '%')) {
                    sFile.write(line);
                    continue;
                }
                QString linStr = QString::fromLocal8Bit(line);

                int leftPos = 0;
                int rightPos = 0;
                int pos = 0;
                for (int i = 0; i <= comma; i++){
                    pos = linStr.indexOf(",", pos + 1);
                    if (i == (comma-1)) {
                        leftPos = pos;
                    }
                    if (i == comma) {
                        rightPos = pos;
                    }
                }
                // Now add the selected line to the file table
                result = hash[linStr.mid(leftPos + 1, rightPos - leftPos -1)];
                if (result > 1) {
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