#include "gand.h"

GAnd::GAnd(int x, int y, long id):GGate(x,y, id) {
    setPixmap(QPixmap(QDir().absolutePath()+"/img/and.png"));
}
