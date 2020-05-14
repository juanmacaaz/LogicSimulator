#include "gxor.h"

GXor::GXor(int x, int y, long id):GGate(x,y,id) {
    setPixmap(QPixmap(QDir().absolutePath()+"/img/xor.png"));
}
