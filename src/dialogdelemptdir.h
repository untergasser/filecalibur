#ifndef DIALOGDELEMPTDIR_H
#define DIALOGDELEMPTDIR_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>

#include "dialogerrormessage.h"

namespace Ui {
class DialogDelEmptDir;
}

class DialogDelEmptDir : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogDelEmptDir(QWidget *parent = 0);
    ~DialogDelEmptDir();
    
    void setErrDB(DialogErrorMessage *err);

private slots:
    void on_pushButtonDir_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_buttonBox_accepted();

private:
    DialogErrorMessage *error;

    Ui::DialogDelEmptDir *ui;
};

#endif // DIALOGDELEMPTDIR_H
