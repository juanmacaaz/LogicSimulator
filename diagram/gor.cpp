#include "gor.h"

GOr::GOr(int x, int y, int id):GGate(x,y) {
    m_id = id;
    setPixmap(QPixmap(QDir().absolutePath()+"/img/or.png"));
}
