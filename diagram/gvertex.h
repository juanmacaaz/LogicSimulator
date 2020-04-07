#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsEllipseItem>

class GGate;
class GCable;

class GVertex: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    enum Position {LEFT, RIGHT};
    GVertex(int x, int y, int w, int h, Position position, GGate* parent);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setPosition(int x, int y);
    void unSelect();
    void addCable(GCable* cable);
    void removeCable(GCable* cable);
    Position getPosition() {return m_position;}
    GGate* getGate() {return m_gate;}
    QList<GCable*> getCables() {return m_cable;}
private:
    Position m_position;
    bool m_selected;
    GGate* m_gate;
    QList<GCable*> m_cable;
signals:
    void newPosition(int x, int y);
    void vertexClick(GVertex* vertex);
};

#endif // VERTEX_H
