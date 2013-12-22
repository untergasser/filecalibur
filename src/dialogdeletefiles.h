#ifndef DIALOGDELETEFILES_H
#define DIALOGDELETEFILES_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
#include <QFile>

#include "dialogerrormessage.h"

namespace Ui {
class DialogDeleteFiles;
}

class DialogDeleteFiles : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogDeleteFiles(QWidget *parent = 0);
    ~DialogDeleteFiles();
    
    void setLoadFile(QString suggestion);
    void setErrDB(DialogErrorMessage *err);

private slots:
    void on_pushButtonLoadFile_clicked();
    void on_pushButtonDir_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_buttonBox_accepted();

private:
    DialogErrorMessage *error;

    Ui::DialogDeleteFiles *ui;
};

#endif // DIALOGDELETEFILES_H
