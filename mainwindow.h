#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <set>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QInputDialog>
#include <sstream>
#include <algorithm>
#include "diagram/diagram.h"
#include "cursor/gcursor.h"
#include "toolbar/diagramtoolbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionGenerate_function_triggered();
    void on_actionGenerate_simulate_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionHelp_triggered();

    void on_btn_click();

    void on_actionExport_to_vhdl_triggered();

private:

    Ui::MainWindow *ui;
    Diagram* scene;
    GCursor* cursor;
    QVBoxLayout* vertical;
    QPushButton* btn;
    QTableWidget* table;
    QLineEdit* input;
    QLineEdit* mimterms;
    QLineEdit* reduction;
    float scale;
};
#endif // MAINWINDOW_H
