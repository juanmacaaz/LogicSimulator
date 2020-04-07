#ifndef GAND_H
#define GAND_H

#include "diagram/ggate.h"

class GAnd : public GGate
{
public:
    GAnd(int x, int y, int id):GGate(x,y) {
        m_element = GGate::AND;
        m_id = id;
        setPixmap(QPixmap(QDir().absolutePath()+"/img/and.png"));
    }
    int getId() { return m_id;};
private:
    int m_id;
    Element m_element;
};

#endif // GAND_H
