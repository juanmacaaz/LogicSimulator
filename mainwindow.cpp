#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    scale = 1;
    ui->setupUi(this);
    cursor = new GCursor();
    scene = new Diagram(cursor);
    ui->graphicsView->setScene(scene);

    /*toolBar = new QToolBar(this);
    toolBar->setOrientation(Qt::Vertical);
    QToolButton* q = new QToolButton();
    q->setIcon(QIcon(QDir().absolutePath()+"/img/inputD.xpm"));
    q->setIconSize(QSize(100,100));
    toolBar->addWidget(q);
    */
   /*
    ui->listWidget->addItem("AND");
    ui->listWidget->addItem("OR");
    ui->listWidget->addItem("XOR");
    ui->listWidget->addItem("INV");
    ui->listWidget->addItem("INPUT");
    ui->listWidget->addItem("OUTPUT");
    ui->listWidget->addItem("DELETE");
    ui->listWidget->addItem("GENERATE FUNCTION");
    ui->listWidget->addItem("GENERATE SIMULATION");
    ui->listWidget->addItem("CHANGE");
    */

    addToolBar(new DiagramToolBar(cursor));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionGenerate_function_triggered()
{
   QMessageBox msgBox;
   msgBox.setText(scene->generateFunction(false));
   msgBox.exec();
}

void MainWindow::on_actionGenerate_simulate_triggered()
{
    QMessageBox msgBox;
    msgBox.setText(scene->generateFunction(true));
    msgBox.exec();
}

void MainWindow::on_actionNew_triggered()
{
    delete scene;
    scene = new Diagram(cursor);
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_actionSave_triggered()
{

}
