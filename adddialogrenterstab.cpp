#include "adddialogrenterstab.h"
#include "ui_adddialogrenterstab.h"
#include <exception>
#include <QMessageBox>

    using namespace std;
addDialogRentersTab::addDialogRentersTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialogRentersTab)
{
    ui->setupUi(this);
}

addDialogRentersTab::~addDialogRentersTab()
{
    delete ui;
}

void addDialogRentersTab::on_okButton_renters_clicked()
{
    try {
        QString name = ui->lineEdit_Name_renters->text();
        QString surname = ui->lineEdit_Surname_renters->text();
        QString fathername = ui->lineEdit_Fathername_renters->text();
        QString number = QString::number(ui->spinBox_Number_renters->value());
        if (name.isEmpty()||surname.isEmpty()||fathername.isEmpty()||number.isEmpty())
        {
            throw exception("Обнаружено незаполненное поле!");
        }
        renter.setName(ui->lineEdit_Name_renters->text());
        renter.setSurname(ui->lineEdit_Surname_renters->text());
        renter.setFathername(ui->lineEdit_Fathername_renters->text());
        renter.setNumber(QString::number(ui->spinBox_Number_renters->value()));
        renter.setDayStart(ui->dateEdit_DateStart_renters->date().day());
        renter.setMonthStart(ui->dateEdit_DateStart_renters->date().month());
        renter.setYearStart(ui->dateEdit_DateStart_renters->date().year());
        renter.setDayFinish(ui->dateEdit_DateFinish_renters->date().day());
        renter.setMonthFinish(ui->dateEdit_DateFinish_renters->date().month());
        renter.setYearFinish(ui->dateEdit_DateFinish_renters->date().year());
        accept();
    } catch (exception &ex) {
        QMessageBox::warning(this,ex.what(),"Пожалуйста, заполните все поля в диалоговом окне.");
    }
}

void addDialogRentersTab::on_cancelButton_renters_clicked()
{
    reject();
}
