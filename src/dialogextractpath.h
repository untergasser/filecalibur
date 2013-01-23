#ifndef DIALOGEXTRACTPATH_H
#define DIALOGEXTRACTPATH_H

#include <QDialog>
#include <QFileDialog>

#include "dialogerrormessage.h"

namespace Ui {
class DialogExtractPath;
}

class DialogExtractPath : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogExtractPath(QWidget *parent = 0);
    ~DialogExtractPath();

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

    Ui::DialogExtractPath *ui;
};

#endif // DIALOGEXTRACTPATH_H
