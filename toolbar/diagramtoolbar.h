#ifndef DIAGRAMTOOLBOX_H
#define DIAGRAMTOOLBOX_H

#define N_ELEMENTS 9

#include <QToolBar>
#include <QIcon>
#include <QVector>
#include "dtoolbutton.h"

class DiagramToolBar: public QToolBar
{
    Q_OBJECT
public:
    DiagramToolBar(GCursor* cursor);
private:
    QVector<DToolButton*> m_toolButtons;
private slots:
    void toolButtonClicked();
};

#endif // DIAGRAMTOOLBOX_H
