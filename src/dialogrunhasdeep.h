#ifndef DIALOGRUNHASDEEP_H
#define DIALOGRUNHASDEEP_H

#include <QDialog>

namespace Ui {
class DialogRunHasDeep;
}

class DialogRunHasDeep : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogRunHasDeep(QWidget *parent = 0);
    ~DialogRunHasDeep();
    
private:
    Ui::DialogRunHasDeep *ui;
};

#endif // DIALOGRUNHASDEEP_H
