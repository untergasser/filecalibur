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

#ifndef DIALOGDIFFTOOL_H
#define DIALOGDIFFTOOL_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
#include <QProcess>
#include <QSettings>

#include "dialogerrormessage.h"

namespace Ui {
class DialogDiffTool;
}

class DialogDiffTool : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogDiffTool(QWidget *parent = 0);
    ~DialogDiffTool();
    
    void setLoadFile(QString suggestion);
    void setErrDB(DialogErrorMessage *err);

public slots:
    void diffUpdateError();
    void diffError(QProcess::ProcessError err);

private slots:
    void on_pushButtonLoadFile_clicked();
    void on_pushButtonLoadFile_2_clicked();
    void on_buttonBox_accepted();

private:
    DialogErrorMessage *error;

    QStringList command;
    QProcess diff_bin;

    Ui::DialogDiffTool *ui;
};

#endif // DIALOGDIFFTOOL_H
