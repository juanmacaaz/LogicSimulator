#ifndef GINV_H
#define GINV_H

#include "diagram/ggate.h"

class GInv : public GGate
{
public:
    GInv(int x, int y, int id):GGate(x, y){
        m_element = GGate::INV;
        m_id = id;
        setPixmap(QPixmap(QDir().absolutePath()+"/img/inv.png"));
    };
    int getId() { return m_id;};
private:
    int m_id;
    Element m_element;
};

#endif // GINV_H
