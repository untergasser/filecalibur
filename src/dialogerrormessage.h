#ifndef DIALOGERRORMESSAGE_H
#define DIALOGERRORMESSAGE_H

#include <QDialog>

namespace Ui {
class DialogErrorMessage;
}

class DialogErrorMessage : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogErrorMessage(QWidget *parent = 0);
    void setError(QString err);
    ~DialogErrorMessage();

    void newErr(QString err);
    void addLast(QString err);
    void addLast(int err);
    void checkForErrors();

private:
    Ui::DialogErrorMessage *ui;
    QStringList error;
};

#endif // DIALOGERRORMESSAGE_H
