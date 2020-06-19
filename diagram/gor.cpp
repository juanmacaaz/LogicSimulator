#include "gor.h"

GOr::GOr(int x, int y, long id):GGate(x,y,id)
{
    setPixmap(QPixmap(QDir().absolutePath()+"/img/or.png"));
}
