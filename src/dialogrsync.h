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

#ifndef DIALOGRSYNC_H
#define DIALOGRSYNC_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>

#include "dialogerrormessage.h"
#include "dialogrunrsync.h"

namespace Ui {
class DialogRsync;
}

class DialogRsync : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogRsync(QWidget *parent = 0);
    ~DialogRsync();
    
    void setErrDB(DialogErrorMessage *err);

private slots:
    void on_pushButtonDirSource_clicked();
    void on_pushButtonDirTarget_clicked();
    void on_buttonBox_accepted();

private:
    DialogErrorMessage *error;
    Ui::DialogRsync *ui;
};

#endif // DIALOGRSYNC_H
