/****************************************************************************
**
**  (c) Copyright 2014 by Dr. Andreas Untergasser
**      All rights reserved.
**
**  This file is part of Filecalibur.
**
**  Filecalibur is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Filecalibur is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Filecalibur.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#ifndef DIALOGEXTRACTPATH_H
#define DIALOGEXTRACTPATH_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>

#include "dialogerrormessage.h"

namespace Ui {
class DialogExtractPath;
}

class DialogExtractPath : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogExtractPath(QWidget *parent = 0);
    ~DialogExtractPath();

    void setLoadFile(QString suggestion);
    void setErrDB(DialogErrorMessage *err);

signals:
    void openResults(QString res);

private slots:
    void on_pushButtonLoadFile_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_buttonBox_accepted();

private:
    DialogErrorMessage *error;

    Ui::DialogExtractPath *ui;
};

#endif // DIALOGEXTRACTPATH_H
