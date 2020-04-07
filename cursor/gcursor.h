#ifndef GCURSOR_H
#define GCURSOR_H

#include "diagram/gvertex.h"
#include "diagram/ggate.h"

class GCursor: public QObject
{
    Q_OBJECT
public:
    enum CursorMode {BASIC, GATE, CABLE, QDELETE, INOUT};
    GCursor();
    void setCursorMode(const CursorMode &cursorMode) {m_cursorMode = cursorMode;}
    CursorMode getCursor() const {return m_cursorMode;}
    void setGateType(const GGate::Element &gateType) {m_gateType = gateType;}
    GGate::Element getElement() const {return m_gateType;}
private:
    GGate::Element m_gateType;
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
