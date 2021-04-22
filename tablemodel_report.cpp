#include "tablemodel_report.h"
#include <QFile>
#include <QDebug>
#include <QComboBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
TableModel_report::TableModel_report(QObject * parent) : QAbstractTableModel(parent)
{

}

int TableModel_report::rowCount(const QModelIndex &parent) const
{
    int cnt = 0;
    QFile file("roomsList.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
    }
    while (!file.atEnd())
    {
        cnt++;
        file.readLine();
    }
    return cnt;
}

int TableModel_report::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TableModel_report::data(const QModelIndex &index, int role) const
{
    int n = 0;
    if( role == Qt::DisplayRole)
    {
        QFile file("monthWorkReport.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){ return 0; }
        while (index.row()!=n)
        {
            QString line = file.readLine();
            n++;
        }
        n = 0;
        QString line = file.readLine();
        if (!file.atEnd())
            line.resize(line.size()-1);
        QRegExp rx("(\\ |\\,|\\.|\\:|\\t)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
        QStringList stringlist = line.split(rx);
        while (index.column()!=n)
        {
            n++;
        }
        return stringlist[n];
    }
    else if (role==Qt::BackgroundColorRole)
    {
        QBrush background;
        QColor color3(139,255,139,150);
        QColor color4(244,255,139,150);
        if (index.column()==0||index.column()==1)
            background=color3;
        else if(index.column()==2||index.column()==3)
            background=color4;
        return background;
    }
    return QVariant();
}

QVariant TableModel_report::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation==Qt::Horizontal)
        {
            switch(section)
            {
            case 0:
                return QString("(Пред.месяц)Занят/");
            case 1:
                return QString("свободен дней номер");
            case 2:
                return QString("(Тек. месяц)Занят/");
            case 3:
                return QString("свободен дней номер");
            default:
                return QString("No such column");
            }
        }
        else
        {
            return section+1;
        }
    }
    return QVariant();
}
