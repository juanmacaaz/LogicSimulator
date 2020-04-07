#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cursor = new GCursor();
    scene = new Diagram(cursor);
    ui->graphicsView->setScene(scene);

    ui->listWidget->addItem("AND");
    ui->listWidget->addItem("OR");
    ui->listWidget->addItem("XOR");
    ui->listWidget->addItem("INV");
    ui->listWidget->addItem("INPUT");
    ui->listWidget->addItem("OUTPUT");
    ui->listWidget->addItem("DELETE");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    cursor->setCursorMode(GCursor::GATE);
    switch (currentRow) {
        case 0: cursor->setGateType(GGate::AND);  break;
        case 1: cursor->setGateType(GGate::OR);   break;
        case 2: cursor->setGateType(GGate::XOR);  break;
        case 3: cursor->setGateType(GGate::INV);  break;
        case 4: cursor->setGateType(GGate::INPUT);
                cursor->setCursorMode(GCursor::INOUT); break;
        case 5: cursor->setGateType(GGate::OUTPUT);
                cursor->setCursorMode(GCursor::INOUT); break;
        case 6: cursor->setCursorMode(GCursor::QDELETE);  break;
    }
}
