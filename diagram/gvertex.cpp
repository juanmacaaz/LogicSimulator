#include "diagram/gvertex.h"
#include "QWidget"
#include <QDebug>

GVertex::GVertex(int x, int y, int w, int h, Position position, GGate* parent)
{
    m_cable = QList<GCable*>();
    m_gate = parent;
    m_selected = false;
    m_position = position;
    setRect(x,y,w,h);
}

void GVertex::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(!m_selected) {
        setBrush(Qt::blue);
        m_selected = true;
    }else {
        setBrush(QBrush());
        m_selected = false;
    }
    emit vertexClick(this);
    QGraphicsItem::mousePressEvent(event);
}

void GVertex::setPosition(int x, int y)
{
    emit newPosition(x, y);
    setX(x);
    setY(y);
}

void GVertex::unSelect()
{
    m_selected = false;
    setBrush(QBrush());
}

void GVertex::addCable(GCable *cable)
{
    m_cable.append(cable);
}

void GVertex::removeCable(GCable *cable)
{
    m_cable.removeAll(cable);
}

