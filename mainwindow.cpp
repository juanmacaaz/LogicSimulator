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

    vertical = new QVBoxLayout();

    input = new QLineEdit(this);
    mimterms = new QLineEdit(this);
    reduction = new QLineEdit(this);

    input->setPlaceholderText("Logic function");

    mimterms->setReadOnly(true);
    reduction->setReadOnly(true);
    reduction->setPlaceholderText("Coming soon...");

    btn = new QPushButton("Compute", this);

    vertical->addWidget(input);

    vertical->addWidget(btn);
    vertical->addWidget(mimterms);
    vertical->addWidget(reduction);

    vertical->setAlignment(Qt::AlignmentFlag::AlignTop);

    ui->contenedor->addLayout(vertical);

    connect(btn, SIGNAL (clicked()),this, SLOT (on_btn_click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionGenerate_function_triggered()
{
    QStringList list;
    QStringList functions;
    QStringList outputs;

    for(QString& t : scene->generateFunction().split("\n"))
        list << t;

    if (list.size() <= 2)
    {
        input->setText(list[0].split("=")[1]);
    }
    else
    {
        list.removeLast();
        for(QString& t : list )
        {
            functions << t.split("=")[1];
            outputs   << t.split("=")[0];
        }
        QString text = QInputDialog::getItem(this, tr("Multiple outputs"), tr("Choise a output"), outputs);
        input->setText(functions[outputs.indexOf(text)]);
    }
    on_btn_click();
}

void MainWindow::on_actionGenerate_simulate_triggered()
{
    QMessageBox msgBox;
    QString msg = "";
    Operation * func;
    QStringList sub_expr;
    QStringList expr = (scene->generateFunction()).split('\n');

    for (QString e : expr)
    {
        sub_expr = e.split('=');

        if (sub_expr.length() >= 2)
        {
            string s_func = sub_expr[1].toStdString();

            quitSpaces(&s_func);
            func = parse(s_func);

            msg += sub_expr[0] + " = ";

            if (func->eval(scene->getInValues()))
                msg += '1';
            else
                msg += '0';

             msg += '\n';
        }
    }
    msgBox.setText(msg);
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
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"", tr("Diagram Files (*.dgm)"));
    QFile f(fileName);
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
    QUrl fileName =  QFileDialog::getOpenFileName(this, tr("Open Diagram"), "", tr("Diagram Files (*.dgm)"));
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

void MainWindow::on_btn_click()
{
    QStringList headerNames;
    Operation* operation;
    vector<string> names;
    int nVars = 0;
    vector<bool> truthTable;
    vector<int> minterms;
    QString mintermsS = "";

    string function = input->text().toStdString();
    string erroMsg;

    if(validInput(function, &erroMsg))
    {
        quitSpaces(&function);
        operation = parse(function);
        operation->getInfo(&nVars, &names);
        truthTable = getTable(operation, nVars, names);
        minterms = getMinterms(truthTable, nVars);

        for(int& x: minterms)
        {
            mintermsS.append(QString::number(x));
            mintermsS.append(" ");
        }
        mimterms->setText(mintermsS);

        //Tabla
        for(string& x: names)
        {
            headerNames << x.c_str();
        }
        headerNames << "out=";

        table = new QTableWidget(pow(2,nVars),nVars+1);
        table->setSortingEnabled(false);

        table->setHorizontalHeaderLabels(headerNames);

        for(int i = 0; i < pow(2,nVars); i++)
        {
            table->setItem(i, nVars, new QTableWidgetItem(to_string(truthTable[i]).c_str()));
        }

        for(int i = 0; i < nVars; i++)
        {
            bool state = true;
            for(int j = 0; j < pow(2,nVars); j++)
            {
                if(((j%(int)pow(2, i))==0))
                    state = !state;

                table->setItem(j, nVars-i-1, new QTableWidgetItem(to_string(state).c_str()));
            }
        }

        table->show();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error", QString(erroMsg.c_str()));
        messageBox.setFixedSize(500,200);
    }
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Ver. LogicSimulator 0.0.4\n"
                   "https://github.com/juanmacaaz/LogicSimulator");
    msgBox.exec();
}


