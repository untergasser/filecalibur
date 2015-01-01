#ifndef DIALOGMANUAL_H
#define DIALOGMANUAL_H

#include <QDialog>

namespace Ui {
class DialogManual;
}

class DialogManual : public QDialog
{
    Q_OBJECT

public:
    explicit DialogManual(QWidget *parent = 0);
    ~DialogManual();

    void setManual(QString text);

private:
    Ui::DialogManual *ui;
};

#endif // DIALOGMANUAL_H
