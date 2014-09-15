#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "dialogabout.h"
#include "dialogoptionen.h"
#include "dialogerrormessage.h"
#include "dialogcalchash.h"
#include "dialogposmatch.h"
#include "dialognegmatch.h"
#include "dialogrunhasdeep.h"
#include "dialogmodifypath.h"
#include "dialogextractpath.h"
#include "dialogremovepath.h"
#include "dialogjoinfiles.h"
#include "dialogpositivehashing.h"
#include "dialognegativehashing.h"
#include "dialogfindduplicates.h"
#include "dialogdifftool.h"
#include "dialogrsync.h"
#include "dialogdeletefiles.h"
#include "dialogdelemptdir.h"
#include "filedatamodel.h"

#include <QProcess>
#include <QFile>
#include <QTableWidget>
#include <QFileDialog>
#include <QSettings>
#include <QUrl>
#include <QDesktopServices>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public slots:
    void run_hashdeep(QStringList command, QString saFi);
    void killHashDeep();
    void hashDeepUpdateError();
    void hashDeepFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void hashDeepError(QProcess::ProcessError err);
    void updateTable(QString fileSt);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionCalculate_Hashes_triggered();

    void updateTable();
    void readFileToMem();
    void readFileToMem(QString fileSt);
    void setFile(QString file_String);

    void on_actionOpen_triggered();
    void on_actionPositive_Matching_triggered();
    void on_actionNegative_Matching_triggered();
    void on_actionSync_Directories_triggered();
    void on_actionModify_Path_triggered();
    void on_actionRemove_Path_triggered();
    void on_actionExtract_Path_triggered();
    void on_actionJoin_Files_triggered();
    void on_actionPositive_Hashing_triggered();
    void on_actionNegative_Hashing_triggered();
    void on_actionSettings_triggered();
    void on_actionFind_Duplicates_triggered();
    void on_actionCompare_Files_triggered();
    void on_actionDelete_Files_from_List_triggered();
    void on_actionDelete_Empty_Directories_triggered();
    void on_actionSupport_triggered();
    void on_actionHashdeep_triggered();
    void on_actionRsync_triggered();
    void on_actionWinmerge_triggered();
    void on_actionTutorials_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

    void on_actionSourceforge_triggered();

private:
    Ui::MainWindow *ui;
    DialogOptionen *optionen;
    DialogErrorMessage *error;
    DialogCalcHash *hashIt;
    DialogPosMatch *hashPos;
    DialogNegMatch *hashNeg;
    DialogDiffTool *diffTool;
    DialogModifyPath *modifyPath;
    DialogRunHasDeep *hashRun;
    DialogRemovePath *removePath;
    DialogExtractPath *extractPath;
    DialogJoinFiles *joinFiles;
    DialogPositiveHashing *positiveHashing;
    DialogNegativeHashing *negativeHashing;
    DialogFindDuplicates *findDuplicates;
    DialogDeleteFiles *deleteFiles;
    DialogDelEmptDir *delEmptDir;

    QString  hashdeep_saveFile;

    QProcess hashdeep_bin;
    QByteArray hashdeep_data;

    QString table_line1;
    QString table_line2;
    QTableWidget *table;
    int table_cols;
    QStringList table_headers;
    QStringList table_content;
    FileDataModel table_model;
    bool table_used;
    QString programVersion;
};

#endif // MAINWINDOW_H
