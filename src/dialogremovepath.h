#ifndef DIALOGREMOVEPATH_H
#define DIALOGREMOVEPATH_H

#include <QDialog>
#include <QFileDialog>

#include "dialogerrormessage.h"

namespace Ui {
class DialogRemovePath;
}

class DialogRemovePath : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogRemovePath(QWidget *parent = 0);
    ~DialogRemovePath();
    
    void setLoadFile(QString suggestion);
    void setErrDB(DialogErrorMessage *err);

signals:
    void openResults(QString res);

private slots:
    void on_pushButtonLoadFile_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_buttonBox_accepted();

private:
    DialogErrorMessage *error;

    Ui::DialogRemovePath *ui;
};

#endif // DIALOGREMOVEPATH_H
