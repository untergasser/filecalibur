#ifndef DIALOGNEGMATCH_H
#define DIALOGNEGMATCH_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class DialogNegMatch;
}

class DialogNegMatch : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogNegMatch(QWidget *parent = 0);
    ~DialogNegMatch();
    void setLoadFile(QString suggestion);

signals:
    void runHashDeep(QStringList com, QString saFi);

private slots:
    void on_pushButtonDir_clicked();
    void on_pushButtonLoadFile_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_buttonBox_accepted();

private:
    Ui::DialogNegMatch *ui;
};

#endif // DIALOGNEGMATCH_H
