#ifndef ANDITEM_H
#define ANDITEM_H


#include "diagram/gvertex.h"
#include <QGraphicsPixmapItem>
#include <QDir>
#include <typeinfo>

class GGate : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum Element { XOR, AND, OR, INV , INPUT, OUTPUT};
    GGate(int x, int y);
    GGate(int x, int y, bool isInput);
    ~GGate();
    GVertex* getVertexA() {return m_vertexA;};
    GVertex* getVertexB() {return m_vertexB;};
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool isEqual(GGate* gate);
protected:
    void moveVertexs(int x, int y);
private:
    GVertex *m_vertexA;
    GVertex *m_vertexB;
signals:
    void gateClicked(GGate* gate);
};

#endif // ANDITEM_H
