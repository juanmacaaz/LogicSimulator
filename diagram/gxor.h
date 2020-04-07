#ifndef GXOR_H
#define GXOR_H

#include "diagram/ggate.h"

class GXor : public GGate
{
public:
    GXor(int x, int y, int id):GGate(x, y) {
        GGate(x, y);
        m_element = GGate::XOR;
        m_id = id;
        setPixmap(QPixmap(QDir().absolutePath()+"/img/xor.png"));
    };
    int getId() { return m_id;};
private:
    int m_id;
    Element m_element;
};

#endif // GXOR_H
