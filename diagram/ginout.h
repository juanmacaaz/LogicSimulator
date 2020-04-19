#ifndef GINPUT_H
#define GINPUT_H

#include <QString>
#include <QGraphicsTextItem>
#include "ggate.h"

class GInOut: public GGate
{
public:
    GInOut(int x, int y, bool isInput, long varName):GGate(x, y) {
        m_isInput = isInput;
        m_varName = varName;
        if(isInput) {
            m_element = GGate::INPUT;
            setPixmap(QPixmap(QDir().absolutePath()+"/img/input.png"));
        }else {
            m_element = GGate::OUTPUT;
            setPixmap(QPixmap(QDir().absolutePath()+"/img/output.png"));
        }
        m_text.setX(x+70);
        m_text.setY(y+90);
    }
    QGraphicsTextItem* getText() {return &m_text;}
    long getVarName() { return m_varName;};
    bool getIOType() {return m_isInput;}
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    long getId() const {return m_varName;}
private:
    bool m_isInput;
    long m_varName;
    GGate::Element m_element;
    QGraphicsTextItem m_text;
};

#endif // GINPUT_H
