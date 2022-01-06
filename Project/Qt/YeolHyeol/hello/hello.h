#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_hello.h"

class hello : public QMainWindow
{
    Q_OBJECT

public:
    hello(QWidget *parent = Q_NULLPTR);

private:
    Ui::helloClass ui;
};
