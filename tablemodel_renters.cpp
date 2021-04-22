#include "tablemodel_renters.h"
#include <QFile>
#include <QDebug>
#include <QComboBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBrush>

TableModel_renters::TableModel_renters(QObject * parent) : QAbstractTableModel(parent)
{
}

int TableModel_renters::rowCount(const QModelIndex &parent) const
{
    int cnt = 0;
    QFile file("rentersList.txt");
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

int TableModel_renters::columnCount(const QModelIndex &parent) const
{
    return 10;
}

QVariant TableModel_renters::data(const QModelIndex &index, int role) const
{
    int n = 0;
    if( role == Qt::DisplayRole)
    {
        QFile file("rentersList.txt");
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
        QColor color1(139,178,255,150);
        QColor color2(255,144,144,150);
        QColor color3(139,255,139,150);
        QColor color4(244,255,139,150);
        if (index.column()>=4&&index.column()<=6)
            background=color1;
        else if(index.column()>=7&&index.column()<=9)
            background=color2;
        else if (index.column()<=2)
            background=color3;
        else
            background=color4;
        return background;
    }
    return QVariant();
}

QVariant TableModel_renters::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation==Qt::Horizontal)
        {
            switch(section)
            {
            case 0:
                return QString("Фамилия");
                break;
            case 1:
                return QString("Имя");
                break;
            case 2:
                return QString("Отчество");
                break;
            case 3:
                return QString("Номер");
            case 4:
                return QString("День");
            case 5:
                return QString("Месяц");
            case 6:
                return QString("Год");
            case 7:
                return QString("День");
            case 8:
                return QString("Месяц");
            case 9:
                return QString("Год");
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

void TableModel_renters::sort(int column, Qt::SortOrder order)
{
    MainWindow window;
    window.renters_Data = window.loadDataRentersName("rentersList.txt");
    window.dates_Data = window.loadDataRentersDates("rentersList.txt");
    QList<int> tempint;
    QList<QString> tempstring;
    if (column < 4)
    {
        for (int i = 0; i < window.renters_Data.size() - 1; i++) {
                for (int j = 0; j < window.renters_Data.size() - i - 1; j++) {
                    if ((window.renters_Data[j][column] > window.renters_Data[j + 1][column]&&column<3)
                            ||(window.renters_Data[j][column].toInt() > window.renters_Data[j + 1][column].toInt())) {
                        tempstring = window.renters_Data[j];
                        window.renters_Data[j] = window.renters_Data[j + 1];
                        window.renters_Data[j + 1] = tempstring;
                        tempint = window.dates_Data[j];
                        window.dates_Data[j] = window.dates_Data[j + 1];
                        window.dates_Data[j + 1] = tempint;
                    }
                }
            }
    }
    else if (column > 3)
    {
        for (int i = 0; i < window.dates_Data.size() - 1; i++) {
                for (int j = 0; j < window.dates_Data.size() - i - 1; j++) {
                    if (column >=4 && column <= 6)
                    {
                        if (window.dates_Data[j][2] > window.dates_Data[j + 1][2]||
                                (window.dates_Data[j][2]==window.dates_Data[j+1][2]&&window.dates_Data[j][1]>window.dates_Data[j+1][1])
                                ||(window.dates_Data[j][2]==window.dates_Data[j+1][2]&&window.dates_Data[j][1]==window.dates_Data[j+1][1]
                                &&window.dates_Data[j][0]>window.dates_Data[j+1][0]))
                        {
                            tempstring = window.renters_Data[j];
                            window.renters_Data[j] = window.renters_Data[j + 1];
                            window.renters_Data[j + 1] = tempstring;
                            tempint = window.dates_Data[j];
                            window.dates_Data[j] = window.dates_Data[j + 1];
                            window.dates_Data[j + 1] = tempint;
                        }
                    }
                    else if (column>=7)
                    {
                        if (window.dates_Data[j][5] > window.dates_Data[j + 1][5]||
                                (window.dates_Data[j][5]==window.dates_Data[j+1][5]&&window.dates_Data[j][4]>window.dates_Data[j+1][4])
                                ||(window.dates_Data[j][5]==window.dates_Data[j+1][5]&&window.dates_Data[j][4]==window.dates_Data[j+1][4]
                                &&window.dates_Data[j][3]>window.dates_Data[j+1][3]))
                        {
                            tempstring = window.renters_Data[j];
                            window.renters_Data[j] = window.renters_Data[j + 1];
                            window.renters_Data[j + 1] = tempstring;
                            tempint = window.dates_Data[j];
                            window.dates_Data[j] = window.dates_Data[j + 1];
                            window.dates_Data[j + 1] = tempint;
                        }
                    }
                }
            }
    }
    window.saveDatarenters("rentersList.txt", window.renters_Data,window.dates_Data);
}

bool TableModel_renters::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if (!checkIndex(index))
            return false;
        MainWindow window;
        window.renters_Data = window.loadDataRentersName("rentersList.txt");
        window.dates_Data = window.loadDataRentersDates("rentersList.txt");
        if (!value.toString().isEmpty())
        {
            if (index.column()<4)
                window.renters_Data[index.row()][index.column()] = value.toString();
            else if (index.column()>3)
                window.dates_Data[index.row()][index.column()-4] = value.toInt();
        }
        else
            return false;
        window.saveDatarenters("rentersList.txt", window.renters_Data,window.dates_Data);
        window.ifDataChanged("monthWorkReport.txt");
        return true;
    }
    return false;
}

Qt::ItemFlags TableModel_renters::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
