#include "ginout.h"

GInOut::GInOut(int x, int y, long id): GGate(x, y, id)
{
    m_text.setX(x-5);
    m_text.setY(y+50);
}

void GInOut::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    m_text.setX(x()+65);
    m_text.setY(y()+90);
    moveVertexs(x(), y());
}
