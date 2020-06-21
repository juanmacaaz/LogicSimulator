#include "gin.h"

GIn::GIn(int x,int y, long id):GInOut(x, y, id) {
    setPixmap(QPixmap(QDir().absolutePath()+"/img/inputD.png"));
    m_active = false;
    n++;
}

void GIn::active()
{
    setPixmap(QPixmap(QDir().absolutePath()+"/img/inputE.png"));
    m_active = true;
}

void GIn::disActive()
{
    setPixmap(QPixmap(QDir().absolutePath()+"/img/inputD.png"));
    m_active = false;
}

int GIn::n{0};
