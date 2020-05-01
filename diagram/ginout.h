#ifndef GINPUT_H
#define GINPUT_H

#include <QString>
#include <QGraphicsTextItem>
#include "ggate.h"

class GInOut: public GGate
{
public:
    GInOut(int x, int y, long id);
    QGraphicsTextItem* getText() {return &m_text;}
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    QGraphicsTextItem m_text;
};

#endif // GINPUT_H
