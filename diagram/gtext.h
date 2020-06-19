#ifndef GTEXT_H
#define GTEXT_H

#include <QGraphicsTextItem>

class Diagram;

class GText: public QGraphicsTextItem
{
    Q_OBJECT
public:
    GText(){};
private:
    Diagram* m_parent;
    QString m_tmpName;
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
signals:
    void nameChange(const QString& varName, bool& repited);
};

#endif // GTEXT_H
