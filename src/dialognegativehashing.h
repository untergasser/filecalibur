#ifndef DIALOGNEGATIVEHASHING_H
#define DIALOGNEGATIVEHASHING_H

#include <QDialog>
#include <QFileDialog>
#include <QHash>

#include "dialogerrormessage.h"

namespace Ui {
class DialogNegativeHashing;
}

class DialogNegativeHashing : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogNegativeHashing(QWidget *parent = 0);
    ~DialogNegativeHashing();
    
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

    Ui::DialogNegativeHashing *ui;
};

#endif // DIALOGNEGATIVEHASHING_H
