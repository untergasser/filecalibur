#ifndef DIALOGRSYNC_H
#define DIALOGRSYNC_H

#include <QDialog>
#include <QFileDialog>

#include "dialogerrormessage.h"
#include "dialogrunrsync.h"

namespace Ui {
class DialogRsync;
}

class DialogRsync : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogRsync(QWidget *parent = 0);
    ~DialogRsync();
    
    void setErrDB(DialogErrorMessage *err);

private slots:
    void on_pushButtonDirSource_clicked();
    void on_pushButtonDirTarget_clicked();
    void on_buttonBox_accepted();

private:
    DialogErrorMessage *error;
    Ui::DialogRsync *ui;
};

#endif // DIALOGRSYNC_H
