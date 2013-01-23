#ifndef DIALOGRUNRSYNC_H
#define DIALOGRUNRSYNC_H

#include <QDialog>
#include <QProcess>

#include "dialogerrormessage.h"

namespace Ui {
class DialogRunRsync;
}

class DialogRunRsync : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogRunRsync(QWidget *parent = 0);
    ~DialogRunRsync();
    void setCommand(QStringList com);
    void setErrDB(DialogErrorMessage *err);
    void runRsync();

public slots:
    void killRsync();
    void rsyncUpdateText();
    void rsyncUpdateError();
    void rsyncFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void rsyncError(QProcess::ProcessError error);

private:    
    DialogErrorMessage *error;

    Ui::DialogRunRsync *ui;
    QStringList command;

    bool rsync_running;
    QProcess rsync_bin;
    QByteArray rsync_data;
    QString ErrorMessage;

};

#endif // DIALOGRUNRSYNC_H
