#ifndef DIALOGMODIFYPATH_H
#define DIALOGMODIFYPATH_H

#include <QDialog>
#include <QFileDialog>
#include <QMap>
#include <QMapIterator>

#include "dialogerrormessage.h"

namespace Ui {
class DialogModifyPath;
}

class DialogModifyPath : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogModifyPath(QWidget *parent = 0);
    ~DialogModifyPath();

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

    Ui::DialogModifyPath *ui;
};

#endif // DIALOGMODIFYPATH_H
