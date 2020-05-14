#include "gout.h"

GOut::GOut(int x,int y, long id):GInOut(x, y, id) {
    setPixmap(QPixmap(QDir().absolutePath()+"/img/output.png"));
};
