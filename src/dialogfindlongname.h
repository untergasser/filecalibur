#ifndef DIALOGFINDLONGNAME_H
#define DIALOGFINDLONGNAME_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
#include <QHash>

#include "dialogerrormessage.h"

namespace Ui {
class DialogFindLongName;
}

class DialogFindLongName : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFindLongName(QWidget *parent = 0);
    ~DialogFindLongName();

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

    Ui::DialogFindLongName *ui;
};

#endif // DIALOGFINDLONGNAME_H
