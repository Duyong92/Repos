#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDesignerError.h"

class QtDesignerError : public QMainWindow
{
    Q_OBJECT

public:
    QtDesignerError(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtDesignerErrorClass ui;
};
