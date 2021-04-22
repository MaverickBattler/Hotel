#ifndef ADDDIALOGWORKERSTAB_H
#define ADDDIALOGWORKERSTAB_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class addDialogWorkersTab;
}

class addDialogWorkersTab : public QDialog
{
    Q_OBJECT
public:
    explicit addDialogWorkersTab(QWidget *parent = nullptr);
    ~addDialogWorkersTab();
    Worker getWorker() {return worker;}

private slots:
    void on_okButton_workers_clicked();

    void on_cancelButton_workers_clicked();

private:
    Worker worker;
    Ui::addDialogWorkersTab *ui;
};

#endif // ADDDIALOGWORKERSTAB_H
