#ifndef DIALOGPOSITIVEHASHING_H
#define DIALOGPOSITIVEHASHING_H

#include <QDialog>
#include <QFileDialog>
#include <QHash>

#include "dialogerrormessage.h"

namespace Ui {
class DialogPositiveHashing;
}

class DialogPositiveHashing : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogPositiveHashing(QWidget *parent = 0);
    ~DialogPositiveHashing();
    
    void setLoadFile(QString suggestion);
    void setErrDB(DialogErrorMessage *err);

signals:
    void openResults(QString res);

private slots:
    void on_pushButtonLoadFile_clicked();
    void on_pushButtonLoadHash_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_buttonBox_accepted();

private:
    DialogErrorMessage *error;

    Ui::DialogPositiveHashing *ui;
};

#endif // DIALOGPOSITIVEHASHING_H
