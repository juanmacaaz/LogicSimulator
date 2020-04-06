#ifndef GCURSOR_H
#define GCURSOR_H

#include "diagram/element.h"
#include "diagram/gvertex.h"
#include "diagram/ggate.h"
#include "cursor/cursormode.h"

class GCursor: public QObject
{
    Q_OBJECT
public:
    GCursor();
    void setCursorMode(const CursorMode &cursorMode) {m_cursorMode = cursorMode;}
    CursorMode getCursor() const {return m_cursorMode;}
    void setGateType(const Element &gateType) {m_gateType = gateType;}
    Element getElement() const {return m_gateType;}
private:
    Element m_gateType;
    short int m_curretnVertex;
    GVertex* m_vertex[2];
    GGate* m_currentGate;
    CursorMode m_cursorMode;
private slots:
    void vertexIsClick(GVertex* vertex);
signals:
    void cableCreated(GVertex* vertexA, GVertex* vertexB);
};

#endif // GCURSOR_H
