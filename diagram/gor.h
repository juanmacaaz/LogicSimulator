#ifndef GOR_H
#define GOR_H

#include "diagram/ggate.h"
#include "diagram/element.h"

class GOr : public GGate
{
public:
    GOr(int x, int y, int id):GGate(x,y) {
        m_element = Element::OR;
        m_id = id;
        setPixmap(QPixmap(QDir().absolutePath()+"/img/or.png"));
    }
private:
    int m_id;
    Element m_element;
};

#endif // GOR_H
