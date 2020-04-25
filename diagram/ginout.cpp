#include "ginout.h"
#include <QDebug>

void GInOut::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    m_text.setX(x()+65);
    m_text.setY(y()+90);
    moveVertexs(x(), y());
}
