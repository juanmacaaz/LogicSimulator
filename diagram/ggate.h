#ifndef ANDITEM_H
#define ANDITEM_H

#include <QGraphicsPixmapItem>
#include <QDir>
#include <typeinfo>
#include "diagram/gvertex.h"

class GGate : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum Element { XOR, AND, OR, INV , INPUT, OUTPUT};
    GGate(int x, int y, long id);
    ~GGate();
    GVertex* getVertexA() const {return m_vertexA;};
    GVertex* getVertexB() const {return m_vertexB;};
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool isEqual(GGate* gate);
    long getId() const { return m_id;}
    void disActiveVertex();
protected:
    void moveVertexs(int x, int y);
private:
    GVertex *m_vertexA;
    GVertex *m_vertexB;
    long m_id;
signals:
    void gateClicked(GGate* gate);
};

#endif // ANDITEM_H
