#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QListWidgetItem>
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

private:
    Ui::MainWindow *ui;
    Diagram *scene;
    GCursor* cursor;
    float scale;
};
#endif // MAINWINDOW_H
