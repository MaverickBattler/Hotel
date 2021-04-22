#include "adddialogworkerstab.h"
#include "ui_adddialogworkerstab.h"
#include <QDebug>
#include <exception>
#include <QMessageBox>

using namespace std;

addDialogWorkersTab::addDialogWorkersTab(QWidget *parent) :
    QDialog(parent,Qt::WindowCloseButtonHint),
    ui(new Ui::addDialogWorkersTab)
{
    ui->setupUi(this);
}

addDialogWorkersTab::~addDialogWorkersTab()
{
    delete ui;
}

void addDialogWorkersTab::on_okButton_workers_clicked()
{
    QString workerName = ui->lineEdit_Name_workers->text();
    QString workerSurname = ui->lineEdit_Surname_workers->text();
    QString workerFathername = ui->lineEdit_Fathername_workers->text();
    QString workerJobPosition = ui->lineEdit_JobPosition_workers->text();
    try {
        if (workerName.isEmpty()||workerSurname.isEmpty()||workerFathername.isEmpty()||workerJobPosition.isEmpty())
        {
            throw exception("Обнаружено незаполненное поле!");
        }
        worker.setName(ui->lineEdit_Name_workers->text());
        worker.setSurname(ui->lineEdit_Surname_workers->text());
        worker.setFathername(ui->lineEdit_Fathername_workers->text());
        worker.setPosition(ui->lineEdit_JobPosition_workers->text());
        accept();
    } catch (exception &ex) {
        QMessageBox::warning(this,ex.what(),"Пожалуйста, заполните все поля в диалоговом окне.");
    }
}

void addDialogWorkersTab::on_cancelButton_workers_clicked()
{
    reject();
}
