#include "tablemodel_rooms.h"
#include <QFile>
#include <QDebug>
#include <QComboBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <exception>

using namespace std;

TableModel_rooms::TableModel_rooms(QObject * parent) : QAbstractTableModel(parent)
{
}

int TableModel_rooms::rowCount(const QModelIndex &parent) const
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

int TableModel_rooms::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TableModel_rooms::data(const QModelIndex &index, int role) const
{
    int n = 0;
    if( role == Qt::DisplayRole)
    {
        QFile file("roomsList.txt");
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
        if (n!=3)
            return stringlist[n];
        else
            if (stringlist[n]=="1")
                return "Свободен";
            else if (stringlist[n]=="0")
                return "Занят";
    }
    else if (role==Qt::BackgroundColorRole)
    {
        QBrush background;
        QColor color1(139,178,255,150);
        QColor color2(255,213,139,150);
        QColor color3(139,255,139,150);
        QColor color4(244,255,139,150);
        if (index.column()==0)
            background=color4;
        else if (index.column()==1)
            background=color1;
        else if (index.column()==2)
            background=color2;
        else
            background=color3;
        return background;
    }
    return QVariant();
}

QVariant TableModel_rooms::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation==Qt::Horizontal)
        {
            switch(section)
            {
            case 0:
                return QString("Номер");
                break;
            case 1:
                return QString("Места");
                break;
            case 2:
                return QString("Стоимость");
                break;
            case 3:
                return QString("Занятость");
            default:
                return QString("No such column");
            }
        }
    }
    return QVariant();
}

void TableModel_rooms::sort(int column, Qt::SortOrder order)
{
    MainWindow window;
    window.rooms_Data = window.loadDataint("roomsList.txt");
    QList<int> temp;
    for (int i = 0; i < window.rooms_Data.size() - 1; i++) {
            for (int j = 0; j < window.rooms_Data.size() - i - 1; j++) {
                if (window.rooms_Data[j][column] > window.rooms_Data[j + 1][column]) {
                    temp = window.rooms_Data[j];
                    window.rooms_Data[j] = window.rooms_Data[j + 1];
                    window.rooms_Data[j + 1] = temp;
                }
            }
        }
    window.saveDataint("roomsList.txt", window.rooms_Data);
}

struct wrongInputFormat : std::exception
{
    wrongInputFormat(const std::string& s) : std::exception(s.c_str())
    {
        MainWindow * window = new MainWindow();
        QMessageBox::warning(window,s.c_str(),"Пожалуйста, введите 1('свободен','Свободен'), или 0('занят','Занят').");
    }
};

bool TableModel_rooms::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        try {
            if (!checkIndex(index))
                return false;
            MainWindow * window = new MainWindow();
            window->rooms_Data = window->loadDataint("roomsList.txt");
            if (index.column()==3)
            {
                if (!(value.toString()=="1"||value.toString()=="Свободен"||value.toString()=="свободен")&&
                        !(value.toString()=="0"||value.toString()=="Занят"||value.toString()=="занят"))
                    throw wrongInputFormat("Неверный формат ввода!");
                if (value.toString()=="1"||value.toString()=="Свободен"||value.toString()=="свободен")
                    window->rooms_Data[index.row()][index.column()] = 1;
                else if (value.toString()=="0"||value.toString()=="Занят"||value.toString()=="занят")
                    window->rooms_Data[index.row()][index.column()] = 0;
            }
            else if (!value.toString().isEmpty())
                window->rooms_Data[index.row()][index.column()] = value.toInt();
            else
                return false;
            window->saveDataint("roomsList.txt", window->rooms_Data);
            return true;
        } catch (wrongInputFormat(&ex)) {
            return false;
        }
    }
    return false;
}

Qt::ItemFlags TableModel_rooms::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

