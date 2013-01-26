#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

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
#include "filedatamodel.h"

#include <QProcess>
#include <QFile>
#include <QTableWidget>
#include <QFileDialog>

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
};

#endif // MAINWINDOW_H
