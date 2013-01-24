#ifndef DIALOGOPTIONEN_H
#define DIALOGOPTIONEN_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
class DialogOptionen;
}

class DialogOptionen : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogOptionen(QWidget *parent = 0);
    ~DialogOptionen();
    
private slots:
    void on_pushButtonHashdeep_clicked();

    void on_pushButtonRsync_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogOptionen *ui;
};

#endif // DIALOGOPTIONEN_H
