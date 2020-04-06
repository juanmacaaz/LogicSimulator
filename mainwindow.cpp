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
    ui->listWidget->addItem("DELETE");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    cursor->setCursorMode(CursorMode::GATE);
    switch (currentRow) {
        case 0: cursor->setGateType(Element::AND);  break;
        case 1: cursor->setGateType(Element::OR);   break;
        case 2: cursor->setGateType(Element::XOR);  break;
        case 3: cursor->setGateType(Element::INV);  break;
        case 4: cursor->setCursorMode(CursorMode::QDELETE);  break;
    }
}
