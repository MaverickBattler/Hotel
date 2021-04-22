#ifndef ADDDIALOGROOMSTAB_H
#define ADDDIALOGROOMSTAB_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class addDialogRoomsTab;
}

class addDialogRoomsTab : public QDialog
{
    Q_OBJECT

public:
    explicit addDialogRoomsTab(QWidget *parent = nullptr);
    ~addDialogRoomsTab();

    int getNumber() const;

    int getSpace() const;

    int getPrice() const;

    bool getIsfree() const;

private slots:
    void on_okButton_rooms_clicked();

    void on_cancelButton_rooms_clicked();

private:
    int number;
    int space;
    int price;
    bool isfree;
    Ui::addDialogRoomsTab *ui;
};

#endif // ADDDIALOGROOMSTAB_H
