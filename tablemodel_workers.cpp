#include "tablemodel_workers.h"
#include <QFile>
#include <QDebug>

TableModel_workers::TableModel_workers(QObject * parent) : QAbstractTableModel(parent)
{

}

int TableModel_workers::rowCount(const QModelIndex &parent) const
{
    int cnt = 0;
    QFile file("workersList.txt");
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

int TableModel_workers::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TableModel_workers::data(const QModelIndex &index, int role) const
{
    int n = 0;
    if( role == Qt::DisplayRole)
    {
        QFile file("workersList.txt");
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
        if (index.column()<=2)
            background=color3;
        else background=color4;
        return background;
    }
    return QVariant();
}

QVariant TableModel_workers::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Должность");
                break;
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

void TableModel_workers::sort(int column, Qt::SortOrder order)
{
    MainWindow window;
    window.workers_Data = window.loadData("workersList.txt");
    QStringList temp;
    for (int i = 0; i < window.workers_Data.size() - 1; i++) {
            for (int j = 0; j < window.workers_Data.size() - i - 1; j++) {
                if (window.workers_Data[j][column] > window.workers_Data[j + 1][column]) {
                    // меняем элементы местами
                    temp = window.workers_Data[j];
                    window.workers_Data[j] = window.workers_Data[j + 1];
                    window.workers_Data[j + 1] = temp;
                }
            }
        }
    window.saveData("workersList.txt", window.workers_Data);
}

bool TableModel_workers::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if (!checkIndex(index))
            return false;
        MainWindow window;
        window.workers_Data = window.loadData("workersList.txt");
        if (!value.toString().isEmpty())
            window.workers_Data[index.row()][index.column()] = value.toString();
        else
            return false;
        window.saveData("workersList.txt", window.workers_Data);        
        return true;
    }
    return false;
}

Qt::ItemFlags TableModel_workers::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
