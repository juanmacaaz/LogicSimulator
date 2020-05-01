#include "ginout.h"
#include <QDebug>

GInOut::GInOut(int x, int y, long varName): GGate(x, y)
{
    m_varName = varName;
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
