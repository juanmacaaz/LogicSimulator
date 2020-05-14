#ifndef GINPUT_H
#define GINPUT_H

#include <QString>
#include "ggate.h"
#include "gtext.h"

class GInOut: public GGate
{
public:
    GInOut(int x, int y, long id);
    GText* getText() {return &m_text;}
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    GText m_text;
};

#endif // GINPUT_H
