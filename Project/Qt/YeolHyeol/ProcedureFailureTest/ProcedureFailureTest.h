#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProcedureFailureTest.h"

class ProcedureFailureTest : public QMainWindow
{
    Q_OBJECT

public:
    ProcedureFailureTest(QWidget *parent = Q_NULLPTR);

private:
    Ui::ProcedureFailureTestClass ui;
};
