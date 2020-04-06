#ifndef GXOR_H
#define GXOR_H

#include "diagram/ggate.h"
#include "diagram/element.h"

class GXor : public GGate
{
public:
    GXor(int x, int y, int id):GGate(x, y) {
        GGate(x, y);
        m_element = Element::XOR;
        m_id = id;
        setPixmap(QPixmap(QDir().absolutePath()+"/img/xor.png"));
    };
private:
    int m_id;
    Element m_element;
};

#endif // GXOR_H
