#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QAbstractTableModel>
#include <QDialog>
#include <QtCore>
#include <QtGui>

class CustomTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    CustomTable(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};


#endif // CUSTOMTABLE_H
