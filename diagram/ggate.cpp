#include "diagram/ggate.h"
#include <QDebug>
#include "GatePosition.h"

GGate::GGate(int x, int y)
{
    setX(x);
    setY(y);

    setFlag(QGraphicsPixmapItem::ItemIsMovable, true);

    m_vertexA = new GVertex(0, 0, 20, 20, Position::LEFT, this);
    m_vertexB = new GVertex(0, 0, 20, 20, Position::RIGHT, this);

    moveVertexs(x, y);
}

void GGate:: mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);
    moveVertexs(x(), y());
}

void GGate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit gateClicked(this);
    QGraphicsItem::mousePressEvent(event);
}

bool GGate::isEqual(GGate *gate)
{
    return (gate->getVertexA()==m_vertexA&&gate->getVertexB()==m_vertexB);
}

void GGate:: moveVertexs(int x, int y) {
    m_vertexA->setPosition(x-20, y+30);
    m_vertexB->setPosition(x+150, y+30);
}
