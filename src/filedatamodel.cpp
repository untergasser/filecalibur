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

#include "filedatamodel.h"

FileDataModel::FileDataModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void FileDataModel::setup(const int cols, const QStringList head, QStringList *data_in)
{
    colums = cols;
    headers = head;
    data_link = data_in;
    rows = data_link->count();
}

int FileDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED  (parent);
    return rows;
}

int FileDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED (parent);
    return colums;
}

QVariant FileDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole){
        QString linStr = data_link->at(index.row());
        if (index.column() == 0) {
            int pos = 0;
            for (int i = 1; i < colums; i++){
                pos = linStr.indexOf(",", pos + 1);
            }
            pos++;
            return linStr.right(linStr.size() - pos);
        } else {
            QStringList linList = linStr.split(",");
            return linList.at(index.column()-1);
        }
    }
    return QVariant();
}

QVariant FileDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();
    }
    QString lab;
    if (orientation == Qt::Vertical){
        return lab.setNum(section + 1);
    } else {
        return headers.at(section);
    }
    return lab;
}
