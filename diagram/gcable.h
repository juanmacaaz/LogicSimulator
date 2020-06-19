#ifndef LINE_H
#define LINE_H

#include <QGraphicsLineItem>
#include <QPen>
#include <QDynamicPropertyChangeEvent>
#include "diagram/gvertex.h"

class GCable : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    GCable(GVertex* a, GVertex* b);
    bool isEqual(GCable* cable);
    GVertex* getVertexA() const {return m_a;}
    GVertex* getVertexB() const {return m_b;}
private:
    GVertex* m_a;
    GVertex* m_b;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void positionChangeA(int, int);
    void positionChangeB(int, int);
signals:
    void cableClick(GCable* cable);
};

#endif // LINE_H
