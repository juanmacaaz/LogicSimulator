#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QGraphicsScene>
#include <QList>
#include "diagram/gand.h"
#include "diagram/gor.h"
#include "diagram/ginv.h"
#include "diagram/gxor.h"
#include "diagram/gcable.h"
#include "diagram/ggate.h"
#include "cursor/gcursor.h"
#include "diagram/ginout.h"


class Diagram : public QGraphicsScene
{
    Q_OBJECT
public:
    Diagram(GCursor* m_cursor);
private:
    GCursor* m_cursor;
    QList<GGate*> m_gates;
    QList<GCable*> m_lines;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void addGate(GGate::Element type, int x, int y);
    void deleteGate(GGate* gate);
    void addCable(GVertex* a, GVertex* b);
    void deleteCable(GCable* cable);
    void addInOut(GGate::Element type, int x, int y);
    bool isInCableList(GCable* cable);
    void listLines();
public slots:
    void cableIsCreated(GVertex* a, GVertex* b);
    void cableIsCliked(GCable* cable);
    void gateIsClicked(GGate* gate);
};

#endif // DIAGRAM_H
