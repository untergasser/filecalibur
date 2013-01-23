#ifndef FILEDATAMODEL_H
#define FILEDATAMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

class FileDataModel : public QAbstractTableModel
{
public:
    FileDataModel(QObject *parent = 0);
    void setup(const int cols, const QStringList head, QStringList *data_in);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    int colums;
    int rows;
    QStringList headers;
    QStringList *data_link;

};

#endif // FILEDATAMODEL_H
