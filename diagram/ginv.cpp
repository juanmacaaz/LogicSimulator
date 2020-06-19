#include "ginv.h"

GInv::GInv(int x, int y, long id):GGate(x, y, id)
{
    setPixmap(QPixmap(QDir().absolutePath()+"/img/inv.png"));
}
