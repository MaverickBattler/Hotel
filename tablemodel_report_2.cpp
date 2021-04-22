#include "tablemodel_report_2.h"
#include <QFile>
#include <QDebug>
#include <QComboBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
TableModel_report_2::TableModel_report_2(QObject * parent) : QAbstractTableModel(parent)
{

}

int TableModel_report_2::rowCount(const QModelIndex &parent) const
{
    return 1;
}

int TableModel_report_2::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant TableModel_report_2::data(const QModelIndex &index, int role) const
{
    int n = 0;
    if( role == Qt::DisplayRole)
    {
        QFile file("monthWorkReport.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){ return 0; }
        QString line;
        while (!file.atEnd())
        {
            line =file.readLine();
        }
        QRegExp rx("(\\ |\\,|\\.|\\:|\\t)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
        QStringList stringlist = line.split(rx);
        return stringlist[index.column()];
    }
    else if (role==Qt::BackgroundColorRole)
    {
        QBrush background;
        QColor color1(139,178,255,150);
        QColor color2(255,144,144,150);
        if (index.column()==0)
            background=color1;
        else if(index.column()==1)
            background=color2;
        return background;
    }
    return QVariant();
}

QVariant TableModel_report_2::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation==Qt::Horizontal)
        {
            switch(section)
            {
            case 0:
                return QString("Клиентов в прошлый месяц");
            case 1:
                return QString("Клиентов в текущий месяц");
            default:
                return QString("No such column");
            }
        }
    }
    return QVariant();
}
