#ifndef ANDITEM_H
#define ANDITEM_H


#include "diagram/gvertex.h"
#include <QGraphicsPixmapItem>
#include <QDir>

class GGate : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GGate(int x, int y);
    GVertex* getVertexA() {return m_vertexA;};
    GVertex* getVertexB() {return m_vertexB;};
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool isEqual(GGate* gate);
private:
    GVertex *m_vertexA;
    GVertex *m_vertexB;
    void moveVertexs(int x, int y);
signals:
    void gateClicked(GGate* gate);
};

#endif // ANDITEM_H
