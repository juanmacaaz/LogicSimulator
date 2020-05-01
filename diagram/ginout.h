#ifndef GINPUT_H
#define GINPUT_H

#include <QString>
#include <QGraphicsTextItem>
#include "ggate.h"

class GInOut: public GGate
{
public:
    GInOut(int x, int y, long varName);
    QGraphicsTextItem* getText() {return &m_text;}
    long getVarName() { return m_varName;};
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    long getId() const {return m_varName;}
private:
    long m_varName;
    QGraphicsTextItem m_text;
};

#endif // GINPUT_H
