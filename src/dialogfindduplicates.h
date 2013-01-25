#ifndef DIALOGFINDDUPLICATES_H
#define DIALOGFINDDUPLICATES_H

#include <QDialog>
#include <QFileDialog>
#include <QHash>

#include "dialogerrormessage.h"

namespace Ui {
class DialogFindDuplicates;
}

class DialogFindDuplicates : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogFindDuplicates(QWidget *parent = 0);
    ~DialogFindDuplicates();
    
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

    Ui::DialogFindDuplicates *ui;
};

#endif // DIALOGFINDDUPLICATES_H
