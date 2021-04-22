#ifndef TABLEMODEL_REPORT_H
#define TABLEMODEL_REPORT_H

#include <QAbstractTableModel>
#include <QObject>
#include "mainwindow.h"
#include <QHeaderView>
using namespace std;

class TableModel_report : public QAbstractTableModel
{
    Q_OBJECT
    friend MainWindow;
    QList<QList<QString>> renters_Data;
    QList<QList<int>> dates_Data;
public:
    TableModel_report(QObject * parent);
    //Переопределение виртуальных функций класса QAbstractTableModel
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;//Контролирует данные показываемые в каждой ячейке
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // TABLEMODEL_REPORT_H
