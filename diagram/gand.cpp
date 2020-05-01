#include "gand.h"

GAnd::GAnd(int x, int y, int id):GGate(x,y) {
    m_id = id;
    setPixmap(QPixmap(QDir().absolutePath()+"/img/and.png"));
}
