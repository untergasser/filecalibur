#ifndef DIALOGJOINFILES_H
#define DIALOGJOINFILES_H

#include <QDialog>
#include <QFileDialog>

#include "dialogerrormessage.h"

namespace Ui {
class DialogJoinFiles;
}

class DialogJoinFiles : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogJoinFiles(QWidget *parent = 0);
    ~DialogJoinFiles();
    
    void setLoadFile(QString suggestion);
    void setErrDB(DialogErrorMessage *err);

signals:
    void openResults(QString res);

private slots:
    void on_pushButtonLoadFile_clicked();
    void on_pushButtonLoadFile_2_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_buttonBox_accepted();

private:
    DialogErrorMessage *error;

    Ui::DialogJoinFiles *ui;
};

#endif // DIALOGJOINFILES_H
