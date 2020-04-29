#include "gin.h"

GIn::GIn(int x,int y, long id):GInOut(x, y, id) {
    setPixmap(QPixmap(QDir().absolutePath()+"/img/input.png"));
};
