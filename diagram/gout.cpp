#include "gout.h"

GOut::GOut(int x,int y, long id):GInOut(x, y, id) {
    setPixmap(QPixmap(QDir().absolutePath()+"/img/outputD.png"));
}

void GOut::active()
{
    setPixmap(QPixmap(QDir().absolutePath()+"/img/output.png"));
    m_active = true;
}

void GOut::disActive()
{
    setPixmap(QPixmap(QDir().absolutePath()+"/img/outputD.png"));
    m_active = false;
}
