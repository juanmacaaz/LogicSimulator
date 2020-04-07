#ifndef GOR_H
#define GOR_H

#include "diagram/ggate.h"

class GOr : public GGate
{
public:
    GOr(int x, int y, int id):GGate(x,y) {
        m_id = id;
        setPixmap(QPixmap(QDir().absolutePath()+"/img/or.png"));
    }
    long getId() { return m_id;};
private:
    long m_id;
};

#endif // GOR_H
