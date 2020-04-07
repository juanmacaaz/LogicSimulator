#ifndef GXOR_H
#define GXOR_H

#include "diagram/ggate.h"

class GXor : public GGate
{
public:
    GXor(int x, int y, int id):GGate(x, y) {
        GGate(x, y);
        m_id = id;
        setPixmap(QPixmap(QDir().absolutePath()+"/img/xor.png"));
    };
    long getId() { return m_id;};
private:
    long m_id;
};

#endif // GXOR_H
