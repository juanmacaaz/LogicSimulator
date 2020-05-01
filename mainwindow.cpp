#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scale = 1;
    cursor = new GCursor();
    addToolBar(new DiagramToolBar(cursor));
    scene = new Diagram(cursor);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->centerOn(0,0);
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
    ui->graphicsView->setScene(nullptr);
    delete scene;
    scene = new Diagram(cursor);
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"", ".dgm");
    QFile f(fileName+".dgm");
    f.open( QIODevice::WriteOnly);
    f.write(scene->saveDiagram().toUtf8());
    f.close();
}

void MainWindow::on_actionTest_Button_triggered()
{
   qInfo() << scene->saveDiagram();
}

void MainWindow::on_actionOpen_triggered()
{
    QString binary;
    QUrl fileName =  QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.dgm)"));
    QFile file(fileName.url());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        binary+=line;
    }
    delete scene;
    scene = new Diagram(cursor);
    ui->graphicsView->setScene(scene);
    scene->loadDiagram(binary);
}
