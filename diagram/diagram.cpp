#include "diagram/diagram.h"
#include "QDebug"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

Diagram::Diagram(GCursor* cursor)
{
    m_cursor = cursor;
    m_gates = QList<GGate*>();
    m_lines = QList<GCable*>();
    setSceneRect(0, 0, 10000, 10000);
    QObject::connect(m_cursor, SIGNAL(cableCreated(GVertex*, GVertex*)), this, SLOT(cableIsCreated(GVertex*,GVertex*)));
}

void Diagram::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(mouseEvent->button() == Qt::RightButton){
        if(m_cursor->getCursor() == CursorMode::GATE){
            addGate(m_cursor->getElement(), mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
        }
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void Diagram::addGate(Element type, int x, int y)
{
    GGate *newGate;
    switch (type) {
        case Element::AND: newGate = new GAnd(x, y, m_gates.size()); break;
        case Element::OR: newGate = new GOr(x, y, m_gates.size()); break;
        case Element::INV: newGate = new GInv(x, y, m_gates.size()); break;
        case Element::XOR: newGate = new GXor(x, y, m_gates.size()); break;
        default: newGate = new GGate(0,0); break;
    }
    m_gates.push_back(newGate);
    addItem(newGate);
    addItem(newGate->getVertexA());
    addItem(newGate->getVertexB());
    QObject::connect(newGate, SIGNAL(gateClicked(GGate*)), this, SLOT(gateIsClicked(GGate*)));
    QObject::connect(newGate->getVertexA(), SIGNAL(vertexClick(GVertex*)), m_cursor, SLOT(vertexIsClick(GVertex*)));
    QObject::connect(newGate->getVertexB(), SIGNAL(vertexClick(GVertex*)), m_cursor, SLOT(vertexIsClick(GVertex*)));
}

void Diagram::deleteGate(GGate *gate)
{
    m_gates.removeAll(gate);
    removeItem(gate);
    removeItem(gate->getVertexA());
    removeItem(gate->getVertexB());
    for(GCable* cable: gate->getVertexA()->getCables()) {
        deleteCable(cable);
    }
    for(GCable* cable: gate->getVertexB()->getCables()) {
        deleteCable(cable);
    }
}

void Diagram::addCable(GVertex* a, GVertex* b)
{
    GCable* line = new GCable(a,b);
    if(!isInCableList(line)) {
        a->addCable(line);
        b->addCable(line);
        m_lines.push_back(line);
        addItem(line);
        QObject::connect(line, SIGNAL(cableClick(GCable*)), this, SLOT(cableIsCliked(GCable*)));
    }
}

void Diagram::deleteCable(GCable* cable)
{
    cable->getVertexA()->removeCable(cable);
    cable->getVertexB()->removeCable(cable);
    m_lines.removeAll(cable);
    removeItem(cable);
}

bool Diagram::isInCableList(GCable *cable)
{
    for(GCable* line: m_lines) {
        if(line->isEqual(cable)) {
            return true;
        }
    }
    return false;
}

void Diagram::cableIsCreated(GVertex* a, GVertex* b)
{
    if(b->getPosition() == Position::LEFT) {
        addCable(a, b);
    }else {
        addCable(b, a);
    }
    qInfo() << m_lines.size();
}

void Diagram::cableIsCliked(GCable *cable)
{
    if (m_cursor->getCursor() == CursorMode::QDELETE) {
        deleteCable(cable);
        qInfo() << "Eliminar!!";
    }
}

void Diagram::gateIsClicked(GGate *gate)
{
    if (m_cursor->getCursor() == CursorMode::QDELETE) {
        deleteGate(gate);
    }
}
