#ifndef GTEXT_H
#define GTEXT_H

#include<QGraphicsTextItem>

class GText: public QGraphicsTextItem
{
public:
    GText(){};
private:
    QString m_tmpName;
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
};

#endif // GTEXT_H
