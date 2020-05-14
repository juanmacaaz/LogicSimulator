#include "diagram/gcable.h"

GCable::GCable(GVertex* a, GVertex* b)
{
   QPen pen = QPen();
   pen.setWidth(3);
   m_a = a;
   m_b = b;
   QObject::connect(m_a, SIGNAL(newPosition(int,int)), this, SLOT(positionChangeA(int, int)));
   QObject::connect(m_b, SIGNAL(newPosition(int,int)), this, SLOT(positionChangeB(int, int)));
   setLine(a->x() + 20 , a->y() + 10, b->x(), b->y() + 10);
   setPen(pen);
}

bool GCable::isEqual(GCable* cable)
{
    return (cable->m_a==m_a&&cable->m_b==m_b);
}

void GCable::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit cableClick(this);
    QGraphicsItem::mousePressEvent(event);
}


void GCable::positionChangeA(int x, int y)
{
    setLine(x + 20, y + 10, m_b->x(), m_b->y() + 10);
}

void GCable::positionChangeB(int x, int y)
{
    setLine(m_a->x() + 20, m_a->y() + 10, x, y + 10);
}
