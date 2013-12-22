#ifndef DIALOGDIFFTOOL_H
#define DIALOGDIFFTOOL_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
#include <QProcess>
#include <QSettings>

#include "dialogerrormessage.h"

namespace Ui {
class DialogDiffTool;
}

class DialogDiffTool : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogDiffTool(QWidget *parent = 0);
    ~DialogDiffTool();
    
    void setLoadFile(QString suggestion);
    void setErrDB(DialogErrorMessage *err);

public slots:
    void diffUpdateError();
    void diffError(QProcess::ProcessError err);

private slots:
    void on_pushButtonLoadFile_clicked();
    void on_pushButtonLoadFile_2_clicked();
    void on_buttonBox_accepted();

private:
    DialogErrorMessage *error;

    QStringList command;
    QProcess diff_bin;

    Ui::DialogDiffTool *ui;
};

#endif // DIALOGDIFFTOOL_H
