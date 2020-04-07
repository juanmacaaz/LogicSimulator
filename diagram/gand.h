#ifndef GAND_H
#define GAND_H

#include "diagram/ggate.h"

class GAnd : public GGate
{
public:
    GAnd(int x, int y, int id):GGate(x,y) {
        m_id = id;
        setPixmap(QPixmap(QDir().absolutePath()+"/img/and.png"));
    }
    long getId() { return m_id;};
private:
    long m_id;
};

#endif // GAND_H
