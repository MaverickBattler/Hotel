#include "adddialogroomstab.h"
#include "ui_adddialogroomstab.h"

addDialogRoomsTab::addDialogRoomsTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialogRoomsTab)
{
    ui->setupUi(this);
    ui->comboBox_isFree_rooms->addItem("Свободен");
    ui->comboBox_isFree_rooms->addItem("Занят");
}

addDialogRoomsTab::~addDialogRoomsTab()
{
    delete ui;
}

void addDialogRoomsTab::on_okButton_rooms_clicked()
{
    number = ui->spinBox_Number_rooms->value();
    space = ui->spinBox_Space_rooms->value();
    price = ui->spinBox_Price_rooms->value();
    if (ui->comboBox_isFree_rooms->currentText()=="Свободен")
        isfree = true;
    else if (ui->comboBox_isFree_rooms->currentText()=="Занят")
        isfree = false;
    accept();
}

void addDialogRoomsTab::on_cancelButton_rooms_clicked()
{
    reject();
}

bool addDialogRoomsTab::getIsfree() const
{
    return isfree;
}

int addDialogRoomsTab::getPrice() const
{
    return price;
}

int addDialogRoomsTab::getSpace() const
{
    return space;
}

int addDialogRoomsTab::getNumber() const
{
    return number;
}
