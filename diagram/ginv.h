#ifndef GINV_H
#define GINV_H

#include "diagram/ggate.h"

class GInv : public GGate
{
public:
    GInv(int x, int y, int id):GGate(x, y){
        m_id = id;
        setPixmap(QPixmap(QDir().absolutePath()+"/img/inv.png"));
    };
    long getId() { return m_id;};
private:
    long m_id;
};

#endif // GINV_H
