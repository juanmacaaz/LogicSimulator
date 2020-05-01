#include "ginv.h"

GInv::GInv(int x, int y, int id):GGate(x, y){
    m_id = id;
    setPixmap(QPixmap(QDir().absolutePath()+"/img/inv.png"));
};
