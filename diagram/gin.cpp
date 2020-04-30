#include "gin.h"
#include <QDebug>

GIn::GIn(int x,int y, long id):GInOut(x, y, id) {
    setPixmap(QPixmap(QDir().absolutePath()+"/img/inputD.png"));
    m_active = false;
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
