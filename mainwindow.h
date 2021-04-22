#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDate>
#include <ui_mainwindow.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QList<QList<QString>> workers_Data;
    QList<QList<int>> rooms_Data;
    QList<QList<QString>> monthWorkReport_Data;
    QList<QList<QString>> renters_Data;
    QList<QList<int>> dates_Data;
    QList<QList<int>> report_Data;
    QList<QList<QString>> loadData(const QString filename)
    {
        QList<QList<QString>> data;
        QFile file(filename);
        QString datarow;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return data;
        }
        data.clear();
        while (!file.atEnd())
        {
            datarow = file.readLine();
            if (!file.atEnd())
                datarow.resize(datarow.size()-1);
            QRegExp rx("(\\ |\\,|\\:|\\t)"); //RegEx for ' ' or ',' or ':' or '\t'
            QStringList stringlist = datarow.split(rx);
            data.push_back(stringlist);
        }
        return data;
    }
    QList<QList<int>> loadDataint(const QString filename)
    {
        QList<QList<int>> data;
        QFile file(filename);
        QString datarow;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return data;
        }
        data.clear();
        while (!file.atEnd())
        {
            datarow = file.readLine();
            if (!file.atEnd())
                datarow.resize(datarow.size()-1);
            QRegExp rx("(\\ |\\,|\\:|\\t)"); //RegEx for ' ' or ',' or ':' or '\t'
            QStringList stringlist = datarow.split(rx);
            QList<int> listtoadd;
            for (int i = 0; i < stringlist.size();i++)
                listtoadd.push_back(stringlist[i].toInt());
            data.push_back(listtoadd);
        }
        return data;
    }
    QList<QList<QString>> loadDataRentersName(const QString filename)
    {
        QList<QList<QString>> data;
        QFile file(filename);
        QString datarow;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return data;
        }
        data.clear();
        while (!file.atEnd())
        {
            datarow = file.readLine();
            if (!file.atEnd())
                datarow.resize(datarow.size()-1);
            QRegExp rx("(\\ |\\,|\\:|\\.|\\t)");
            QStringList stringlist = datarow.split(rx);
            for (int i = 0; i < 6; i++)
                stringlist.pop_back();
            data.push_back(stringlist);
        }
        return data;
    }
    QList<QList<int>> loadDataRentersDates(const QString filename)
    {
        QList<QList<int>> data;
        QFile file(filename);
        QString datarow;
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return data;
        }
        data.clear();
        while (!file.atEnd())
        {
            datarow = file.readLine();
            if (!file.atEnd())
                datarow.resize(datarow.size()-1);
            QRegExp rx("(\\ |\\,|\\:|\\.|\\t)");
            QStringList stringlist = datarow.split(rx);
            for (int i = 0; i < 4; i++)
                stringlist.pop_front();
            QList<int> listtoadd;
            for (int i = 0; i < stringlist.size();i++)
                listtoadd.push_back(stringlist[i].toInt());
            data.push_back(listtoadd);
        }
        return data;
    }
    void saveData(const QString filename, QList<QList<QString>> data)
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream out(&file);
        out.setCodec("UTF-8");
        for (int i = 0; i < data.size(); i++)
            for (int j = 0; j < data[i].size(); j++)
                if (j!=data[i].size()-1)
                    out << data[i][j] << " ";
                else if (i != data.size()-1)
                    out << data[i][j] << "\n";
                else out << data[i][j];
    }
    void saveDataint(const QString filename, QList<QList<int>> data)
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream out(&file);
        out.setCodec("UTF-8");
        for (int i = 0; i < data.size(); i++)
            for (int j = 0; j < data[i].size(); j++)
                if (j!=data[i].size()-1)
                    out << data[i][j] << " ";
                else if (i != data.size()-1)
                    out << data[i][j] << "\n";
                else out << data[i][j];
    }
    void saveDataReport(const QString filename, QList<QList<int>> data)
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream out(&file);
        out.setCodec("UTF-8");
        for (int i = 0; i < data.size(); i++)
            for (int j = 0; j < data[i].size(); j++)
                if (j!=data[i].size()-1)
                    out << data[i][j] << " ";
                else if (i != data.size()-1)
                    out << data[i][j] << "\n";
                else out << data[i][j];
    }
    void saveDatarenters(const QString filename, QList<QList<QString>> RentersName, QList<QList<int>> RentersDates)
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
             return;
        }
        QTextStream out(&file);
        out.setCodec("UTF-8");
        for (int i = 0; i < RentersName.size(); i++)
        {
            for (int j = 0; j < RentersName[i].size(); j++)
                    out << RentersName[i][j] << " ";
            for (int j = 0; j < RentersDates[i].size(); j++)
                if (j!=RentersDates[i].size()-1)
                    out << RentersDates[i][j] << " ";
                else if (i != RentersDates.size()-1)
                    out << RentersDates[i][j] << "\n";
                else out << RentersDates[i][j];
        }
    }
    void ifDataChanged(const QString filename)
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream out(&file);
        out.setCodec("UTF-8");
        dates_Data = loadDataRentersDates("rentersList.txt");
        renters_Data = loadDataRentersName("rentersList.txt");
        rooms_Data = loadDataint("roomsList.txt");
        int rowsize = rooms_Data.size();
        QList<int> intlist;
        for (int i = 0; i < 4; i++)
            intlist.push_back(0);
        for (int i = 0; i < rowsize; i++)
            report_Data.push_back(intlist);
        for (int row = 0; row < rowsize;row++)
        {
            for (int column = 0;column < 4; column++)
            {
                QDate date;
                date = date.currentDate();
                if (column==0||column==1)
                {
                    if (date.month()!=1)
                        date.setDate(date.year(),date.month()-1,date.day());
                    else
                        date.setDate(date.year()-1,12,date.day());
                }
                QDate startmonth(date.year(),date.month(),1);
                QDate endmonth(date.year(),date.month(),date.daysInMonth());
                QDate enter;
                QDate exit;
                int totaloccupieddays = 0;
                QList<int> occupieddayslist;
                for (int i = 0; i < date.daysInMonth(); i++)
                    occupieddayslist.push_back(0);
                for (int  i = 0; i < dates_Data.size(); i++)
                {
                    if (renters_Data[i][3].toInt()==row+1)
                    {
                        enter.setDate(dates_Data[i][2],dates_Data[i][1],dates_Data[i][0]);
                        exit.setDate(dates_Data[i][5],dates_Data[i][4],dates_Data[i][3]);
                        if ((enter<=startmonth&&exit>=endmonth)||(enter>=startmonth&&enter<=endmonth)||(exit>=startmonth&&exit<=endmonth))
                        {
                            int a=0;
                            int b=0;
                            if (exit>=endmonth)
                                a = date.daysInMonth();
                            else if (exit<=endmonth)
                                a = exit.day();
                            if (enter<startmonth)
                                b = 0;
                            else if (enter >=startmonth)
                                b = enter.day();
                            for (int j = b;j < a; j++)
                                if (occupieddayslist[j]==0)
                                    occupieddayslist[j]=1;
                        }
                    }
                }
                for (int j = 0; j < occupieddayslist.size();j++)
                    totaloccupieddays+=occupieddayslist[j];
                if (column==0||column==2)
                {
                    report_Data[row][column] = totaloccupieddays;
                }
                else if (column==1||column==3)
                {
                    report_Data[row][column] = date.daysInMonth()-totaloccupieddays;
                }
                if ((column==0||column==2)&&report_Data[row][column]==0)
                {
                    report_Data[row][column+1]=date.daysInMonth();
                }
            }
        }
        int clients = 0;
        QDate date;
        date = date.currentDate();
        QList<int> listtoadd;
        if (date.month()!=1)
            date.setDate(date.year(),date.month()-1,date.day());
        else
            date.setDate(date.year()-1,12,date.day());
        QDate startmonth(date.year(),date.month(),1);
        QDate endmonth(date.year(),date.month(),date.daysInMonth());
        QDate enter;
        QDate exit;
        for (int  i = 0; i < dates_Data.size(); i++)
        {
            enter.setDate(dates_Data[i][2],dates_Data[i][1],dates_Data[i][0]);
            exit.setDate(dates_Data[i][5],dates_Data[i][4],dates_Data[i][3]);
            if ((enter<=startmonth&&exit>=endmonth)||(enter>=startmonth&&enter<=endmonth)||(exit>=startmonth&&exit<=endmonth))
            {
                clients++;
            }
        }
        listtoadd.push_back(clients);
        clients=0;
        if (date.month()!=12)
            date.setDate(date.year(),date.month()+1,date.day());
        else
            date.setDate(date.year()+1,1,date.day());
        startmonth.setDate(date.year(),date.month(),1);
        endmonth.setDate(date.year(),date.month(),date.daysInMonth());
        for (int  i = 0; i < dates_Data.size(); i++)
        {
            enter.setDate(dates_Data[i][2],dates_Data[i][1],dates_Data[i][0]);
            exit.setDate(dates_Data[i][5],dates_Data[i][4],dates_Data[i][3]);
            if ((enter<=startmonth&&exit>=endmonth)||(enter>=startmonth&&enter<=endmonth)||(exit>=startmonth&&exit<=endmonth))
            {
                clients++;
            }

        }
        listtoadd.push_back(clients);
        report_Data.push_back(listtoadd);
        saveDataint("monthWorkReport.txt",report_Data);
    }
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_add_workersTab_clicked();

    void on_pushButton_delete_workersTab_clicked();

    void on_comboBox_workersTab_currentIndexChanged(int index);

    void on_pushButton_add_roomsTab_clicked();

    void on_pushButton_delete_roomsTab_clicked();

    void on_comboBox_roomsTab_currentIndexChanged(int index);

    void on_pushButton_add_rentersTab_clicked();

    void on_pushButton_delete_rentersTab_clicked();

    void on_comboBox_rentersTab_currentIndexChanged(int index);

    void on_quitAction_triggered();

    void on_aboutProgramAction_triggered();

    void on_howToUseAction_triggered();

private:
    Ui::MainWindow *ui;
};
//Базовый абстрактный класс
class Human
{
    virtual void setSurname(const QString &value)=0;
    virtual void setName(const QString &value)=0;
    virtual void setFathername(const QString &value)=0;
    virtual QString getSurname() const = 0;
    virtual QString getName() const = 0;
    virtual QString getFathername() const = 0;
};

class Worker:Human
{
    QString surname;
    QString name;
    QString fathername;
    QString position;
public:
    void setSurname(const QString &value) override{surname = value;};
    void setName(const QString &value) override{name = value;};
    void setFathername(const QString &value) override{fathername=value;};
    void setPosition(const QString &value){position = value;};
    QString getSurname() const override{return surname;};
    QString getName() const override{return name;};
    QString getFathername() const override{return fathername;};
    QString getPosition() const {return position;}
};
class Renter:Human
{
    QString surname;
    QString name;
    QString fathername;
    QString number;
    int dayStart;
    int monthStart;
    int yearStart;
    int dayFinish;
    int monthFinish;
    int yearFinish;
public:
    void setSurname(const QString &value) override{surname = value;};
    void setName(const QString &value) override{name = value;};
    void setFathername(const QString &value) override{fathername=value;};
    void setNumber(const QString &value) {number = value;}
    void setDayStart(int value) {dayStart = value;}
    void setMonthStart(int value){monthStart=value;};
    void setYearStart(int value){yearStart=value;};
    void setDayFinish(int value){dayFinish=value;};
    void setMonthFinish(int value){monthFinish=value;};
    void setYearFinish(int value){yearFinish=value;};
    QString getSurname() const override{return surname;};
    QString getName() const override{return name;};
    QString getFathername() const override{return fathername;};
    QString getNumber() const {return number;}
    int getDayStart() const {return dayStart;}
    int getMonthStart() const {return monthStart;}
    int getYearStart() const {return yearStart;}
    int getDayFinish() const {return dayFinish;}
    int getMonthFinish() const {return monthFinish;}
    int getYearFinish() const {return yearFinish;}
};

#endif // MAINWINDOW_H
