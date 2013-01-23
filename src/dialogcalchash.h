#ifndef DIALOGCALCHASH_H
#define DIALOGCALCHASH_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class DialogCalcHash;
}

class DialogCalcHash : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogCalcHash(QWidget *parent = 0);
    ~DialogCalcHash();

signals:
    void runHashDeep(QStringList com, QString saFi);
    
private slots:
    void on_pushButtonDir_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_buttonBox_accepted();

private:
    Ui::DialogCalcHash *ui;
};

#endif // DIALOGCALCHASH_H
