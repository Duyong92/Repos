#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_addressbook.h"

class AddressBook : public QMainWindow
{
    Q_OBJECT

public:
    AddressBook(QWidget *parent = Q_NULLPTR);

private:
    Ui::AddressBookClass ui;
};
