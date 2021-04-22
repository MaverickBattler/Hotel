#ifndef ADDDIALOGRENTERSTAB_H
#define ADDDIALOGRENTERSTAB_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class addDialogRentersTab;
}

class addDialogRentersTab : public QDialog
{
    Q_OBJECT

public:
    explicit addDialogRentersTab(QWidget *parent = nullptr);
    ~addDialogRentersTab();
    Renter getRenter() {return renter;}

private slots:

    void on_okButton_renters_clicked();

    void on_cancelButton_renters_clicked();

private:
    Renter renter;
    Ui::addDialogRentersTab *ui;
};

#endif // ADDDIALOGRENTERSTAB_H
