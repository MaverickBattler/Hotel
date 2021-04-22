#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablemodel_workers.h"
#include "tablemodel_rooms.h"
#include "tablemodel_renters.h"
#include "tablemodel_report.h"
#include "tablemodel_report_2.h"
#include "adddialogworkerstab.h"
#include "adddialogroomstab.h"
#include "adddialogrenterstab.h"
#include <QDebug>
#include <fstream>
#include <string>
#include <QFile>
#include <QTableView>
#include <QComboBox>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TableModel_workers * model1 = new TableModel_workers(this);
    ui->comboBox_workersTab->addItem("-Не выбрано-");
    ui->comboBox_workersTab->addItem("Фамилия");
    ui->comboBox_workersTab->addItem("Имя");
    ui->comboBox_workersTab->addItem("Отчество");
    ui->comboBox_workersTab->addItem("Должность");
    ui->tableView_workersTab->setModel(model1);

    TableModel_rooms * model2 = new TableModel_rooms(this);
    ui->comboBox_roomsTab->addItem("-Не выбрано-");
    ui->comboBox_roomsTab->addItem("Номер");
    ui->comboBox_roomsTab->addItem("Места");
    ui->comboBox_roomsTab->addItem("Стоимость");
    ui->comboBox_roomsTab->addItem("Занятость");
    ui->tableView_roomsTab->setModel(model2);

    TableModel_renters * model3 = new TableModel_renters(this);
    ui->comboBox_rentersTab->addItem("-Не выбрано-");
    ui->comboBox_rentersTab->addItem("Фамилия");
    ui->comboBox_rentersTab->addItem("Имя");
    ui->comboBox_rentersTab->addItem("Отчество");
    ui->comboBox_rentersTab->addItem("Номер");
    ui->comboBox_rentersTab->addItem("Дата приезда");
    ui->comboBox_rentersTab->addItem("Дата выезда");
    ui->tableView_rentersTab->setModel(model3);
    for (int i = 3; i < 10;i++)
        ui->tableView_rentersTab->setColumnWidth(i,60);

    TableModel_report * model4 = new TableModel_report(this);
    ifDataChanged("monthWorkReport.txt");
    ui->tableView_reportTab->setModel(model4);
    for (int i = 0; i < 4;i++)
        ui->tableView_reportTab->setColumnWidth(i,165);

    TableModel_report_2 * model5 = new TableModel_report_2(this);
    ui->tableView_reportTab_2->setModel(model5);
    ui->tableView_reportTab_2->setColumnWidth(0,350);
    ui->tableView_reportTab_2->setColumnWidth(1,350);
    ui->tableView_reportTab_2->setRowHeight(0,50);
    setWindowTitle("Гостиница");
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Вкладка с работниками
void MainWindow::on_pushButton_add_workersTab_clicked()
{
    workers_Data = loadData("workersList.txt");
    QList<QString> addedLine;
    addDialogWorkersTab * dialog = new addDialogWorkersTab(this);
    int res = dialog->exec();
    Worker worker = dialog->getWorker();
    if (res == QDialog::Accepted)
    {
        addedLine.push_back(worker.getSurname());
        addedLine.push_back(worker.getName());
        addedLine.push_back(worker.getFathername());
        addedLine.push_back(worker.getPosition());
        workers_Data.push_back(addedLine);
    }
    saveData("workersList.txt",workers_Data);
    TableModel_workers * model = new TableModel_workers(this);
    ui->tableView_workersTab->setModel(model);
}

void MainWindow::on_pushButton_delete_workersTab_clicked()
{
    workers_Data = loadData("workersList.txt");
    QItemSelectionModel *select = ui->tableView_workersTab->selectionModel();
    QModelIndexList indexlist = select->selectedRows(); // return selected row(s)
    for (int i = 0, j = 0; i < indexlist.size();i++,j++)
        if (workers_Data.size()!=1)
            workers_Data.removeAt(indexlist[i].row()-j);
        else
        {
            workers_Data.removeAt(indexlist[i].row()-j);
            QFile file("workersList.txt");
            file.remove();
        }
    saveData("workersList.txt", workers_Data);
    TableModel_workers * model = new TableModel_workers(this);
    ui->tableView_workersTab->setModel(model);
}

void MainWindow::on_comboBox_workersTab_currentIndexChanged(int index)
{
    if (ui->comboBox_workersTab->itemText(0)=="Фамилия")
    {
        TableModel_workers * model = new TableModel_workers(this);
        model->sort(index);
        ui->tableView_workersTab->setModel(model);
    }
    else if (index!=0)
        ui->comboBox_workersTab->removeItem(0);
}
//Вкладка с комнатами
void MainWindow::on_pushButton_add_roomsTab_clicked()
{
    rooms_Data = loadDataint("roomsList.txt");
    QList<int> addedLine;
    addDialogRoomsTab * dialog = new addDialogRoomsTab(this);
    int res = dialog->exec();
    if (res == QDialog::Accepted)
    {
        addedLine.push_back(dialog->getNumber());
        addedLine.push_back(dialog->getSpace());
        addedLine.push_back(dialog->getPrice());
        if (dialog->getIsfree())
            addedLine.push_back(1);
        else
            addedLine.push_back(0);
        rooms_Data.push_back(addedLine);
    }
    saveDataint("roomsList.txt",rooms_Data);
    TableModel_rooms * model = new TableModel_rooms(this);
    ui->tableView_roomsTab->setModel(model);
}

void MainWindow::on_pushButton_delete_roomsTab_clicked()
{
    rooms_Data = loadDataint("roomsList.txt");
    QItemSelectionModel *select = ui->tableView_roomsTab->selectionModel();
    QModelIndexList indexlist = select->selectedRows(); // return selected row(s)
    for (int i = 0, j = 0; i < indexlist.size();i++,j++)
        if (rooms_Data.size()!=1)
            rooms_Data.removeAt(indexlist[i].row()-j);
        else
        {
            rooms_Data.removeAt(indexlist[i].row()-j);
            QFile file("roomsList.txt");
            file.remove();
        }
    saveDataint("roomsList.txt", rooms_Data);
    TableModel_rooms * model = new TableModel_rooms(this);
    ui->tableView_roomsTab->setModel(model);
}

void MainWindow::on_comboBox_roomsTab_currentIndexChanged(int index)
{
    if (ui->comboBox_roomsTab->itemText(0)=="Номер")
    {
        TableModel_rooms * model = new TableModel_rooms(this);
        model->sort(index);
        ui->tableView_roomsTab->setModel(model);
    }
    else if (index!=0)
        ui->comboBox_roomsTab->removeItem(0);
}
//Вкладка с проживающими
void MainWindow::on_pushButton_add_rentersTab_clicked()
{
    renters_Data = loadDataRentersName("rentersList.txt");
    dates_Data = loadDataRentersDates("rentersList.txt");
    QList<int> addedLineint;
    QList<QString> addedLinestring;
    addDialogRentersTab * dialog = new addDialogRentersTab(this);
    int res = dialog->exec();
    Renter renter = dialog->getRenter();
    if (res == QDialog::Accepted)
    {
        addedLinestring.push_back(renter.getSurname());
        addedLinestring.push_back(renter.getName());
        addedLinestring.push_back(renter.getFathername());
        addedLinestring.push_back(renter.getNumber());
        addedLineint.push_back(renter.getDayStart());
        addedLineint.push_back(renter.getMonthStart());
        addedLineint.push_back(renter.getYearStart());
        addedLineint.push_back(renter.getDayFinish());
        addedLineint.push_back(renter.getMonthFinish());
        addedLineint.push_back(renter.getYearFinish());
        renters_Data.push_back(addedLinestring);
        dates_Data.push_back(addedLineint);
    }
    saveDatarenters("rentersList.txt",renters_Data,dates_Data);
    ifDataChanged("monthWorkReport.txt");
    TableModel_renters * model = new TableModel_renters(this);
    ui->tableView_rentersTab->setModel(model);
}

void MainWindow::on_pushButton_delete_rentersTab_clicked()
{
    renters_Data = loadDataRentersName("rentersList.txt");
    dates_Data = loadDataRentersDates("rentersList.txt");
    QItemSelectionModel *select = ui->tableView_rentersTab->selectionModel();
    QModelIndexList indexlist = select->selectedRows(); // return selected row(s)
    for (int i = 0, j = 0; i < indexlist.size();i++,j++)
        if (renters_Data.size()!=1)
        {
            renters_Data.removeAt(indexlist[i].row()-j);
            dates_Data.removeAt(indexlist[i].row()-j);
        }
        else
        {
            renters_Data.removeAt(indexlist[i].row()-j);
            dates_Data.removeAt(indexlist[i].row()-j);
            QFile file("rentersList.txt");
            file.remove();
        }
    saveDatarenters("rentersList.txt",renters_Data,dates_Data);
    ifDataChanged("monthWorkReport.txt");
    TableModel_renters * model = new TableModel_renters(this);
    ui->tableView_rentersTab->setModel(model);
}

void MainWindow::on_comboBox_rentersTab_currentIndexChanged(int index)
{
    if (ui->comboBox_rentersTab->itemText(0)=="Фамилия")
    {
        TableModel_renters * model = new TableModel_renters(this);
        if (index == 5)
            index = 7;
        model->sort(index);
        ui->tableView_rentersTab->setModel(model);
    }
    else if (index!=0)
        ui->comboBox_rentersTab->removeItem(0);
}
//Пункты меню
void MainWindow::on_quitAction_triggered()
{
    QApplication::quit();
}

void MainWindow::on_aboutProgramAction_triggered()
{
    QMessageBox::about(this,"О программе","Данная программа была разработана Мохнаткином Кириллом, студентом группы "
                                          "8308 2 курса университета СПБГЭТУ 'ЛЭТИ'. "
                                          "Программа представляет собой ПК для администратора гостиницы, позволяет "
                                          "редактировать данные и выводит отчет работы за месяц.");
}

void MainWindow::on_howToUseAction_triggered()
{
    QMessageBox::about(this,"Как работать в этой программе","   Пользователю доступны 4 вкладки: в первой представлены данные о работниках "
                                                            "гостиницы, во второй - о номерах гостиницы и ценах на них, в третьей - информация "
                                                            "о проживающих(проживавших) в гостинице, в четвертой - отчет о работе за текущий и"
                                                            "предыдущий месяц.\n   В первых трех вкладках вы можете редактировать информацию прямо "
                                                            "в клеточках таблиц, либо добавляя или удаляя строки, нажав на соответствующие кнопки "
                                                            "внизу. Также в этих вкладках вам доступна сортировка по разным столбцам. "
                                                            "Данные четвертой вкладки формируются на основе второй и третьей, поэтому редактировать "
                                                            "данные напрямую вы там не сможете. \n"
                                                            "   P.S.В третьей вкладке для каждого проживающего указаны 2 даты: первая дата - дата заезда "
                                                            "в номер, вторая - дата выезда.");
}
