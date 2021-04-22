#ifndef TABLEMODEL_ROOMS_H
#define TABLEMODEL_ROOMS_H

#include <QAbstractTableModel>
#include <QObject>
#include "mainwindow.h"
#include <QHeaderView>
using namespace std;

class TableModel_rooms : public QAbstractTableModel
{
    Q_OBJECT
    friend MainWindow;
public:
    TableModel_rooms(QObject * parent);
    //Переопределение виртуальных функций класса QAbstractTableModel
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role) const override;//Контролирует данные показываемые в каждой ячейке
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
};

#endif // TABLEMODEL_ROOMS_H
