#ifndef DIALOGPOSMATCH_H
#define DIALOGPOSMATCH_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
class DialogPosMatch;
}

class DialogPosMatch : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogPosMatch(QWidget *parent = 0);
    ~DialogPosMatch();
    void setLoadFile(QString suggestion);

signals:
    void runHashDeep(QStringList com, QString saFi);

private slots:
    void on_pushButtonDir_clicked();
    void on_pushButtonLoadFile_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_buttonBox_accepted();

private:
    Ui::DialogPosMatch *ui;
};

#endif // DIALOGPOSMATCH_H
