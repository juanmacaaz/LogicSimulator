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
        if(m_cursor->getCursor() == GCursor::GATE){
            addGate(m_cursor->getElement(), mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
        }else
        if(m_cursor->getCursor() == GCursor::INOUT) {
            addInOut(m_cursor->getElement(), mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
        }
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void Diagram::addGate(GGate::Element type, int x, int y)
{
    GGate *newGate;
    switch (type) {
        case GGate::AND: newGate = new GAnd(x, y, m_gates.size()); break;
        case GGate::OR: newGate = new GOr(x, y, m_gates.size()); break;
        case GGate::INV: newGate = new GInv(x, y, m_gates.size()); break;
        case GGate::XOR: newGate = new GXor(x, y, m_gates.size()); break;
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
    if(gate->getVertexA()!=nullptr) {
        removeItem(gate->getVertexA());
        for(GCable* cable: gate->getVertexA()->getCables()) {
            deleteCable(cable);
        }
    }
    if(gate->getVertexB()!=nullptr) {
        removeItem(gate->getVertexB());
        for(GCable* cable: gate->getVertexB()->getCables()) {
            deleteCable(cable);
        }
    }
    qInfo() << m_lines.size();
    qInfo() << m_gates.size();
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
    listLines();
}

void Diagram::deleteCable(GCable* cable)
{
    cable->getVertexA()->removeCable(cable);
    cable->getVertexB()->removeCable(cable);
    m_lines.removeAll(cable);
    removeItem(cable);
}

void Diagram::addInOut(GGate::Element type, int x, int y)
{
    GInOut* newInout;
    if(type == GGate::INPUT) {
        newInout = new GInOut(x, y, true, "a");
        addItem(newInout->getVertexB());
        QObject::connect(newInout->getVertexB(), SIGNAL(vertexClick(GVertex*)), m_cursor, SLOT(vertexIsClick(GVertex*)));
    }else {
        newInout = new GInOut(x, y, false, "a");
        addItem(newInout->getVertexA());
        QObject::connect(newInout->getVertexA(), SIGNAL(vertexClick(GVertex*)), m_cursor, SLOT(vertexIsClick(GVertex*)));
    }
    m_gates.push_back(newInout);
    addItem(newInout);
    QObject::connect(newInout, SIGNAL(gateClicked(GGate*)), this, SLOT(gateIsClicked(GGate*)));
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

void Diagram::listLines()
{
    for(GCable* lines: m_lines) {
        if(GAnd* v = dynamic_cast<GAnd*>(lines->getVertexA()->getGate())) {
            qInfo() << "AND," << v->getId();
        }else if(GOr* v = dynamic_cast<GOr*>(lines->getVertexA()->getGate())) {
            qInfo() << "OR," << v->getId();
        }else if(GXor* v = dynamic_cast<GXor*>(lines->getVertexA()->getGate())) {
            qInfo() << "XOR," << v->getId();
        }else if(GInv* v = dynamic_cast<GInv*>(lines->getVertexA()->getGate())) {
            qInfo() << "INV," << v->getId();
        }else if(GInOut* v = dynamic_cast<GInOut*>(lines->getVertexA()->getGate())) {
            qInfo() << "INOUT," << v->getVarName();
        }

        if(GAnd* v = dynamic_cast<GAnd*>(lines->getVertexB()->getGate())) {
            qInfo() << "AND," << v->getId();
        }else if(GOr* v = dynamic_cast<GOr*>(lines->getVertexB()->getGate())) {
            qInfo() << "OR," << v->getId();
        }else if(GXor* v = dynamic_cast<GXor*>(lines->getVertexB()->getGate())) {
            qInfo() << "XOR," << v->getId();
        }else if(GInv* v = dynamic_cast<GInv*>(lines->getVertexB()->getGate())) {
            qInfo() << "INV," << v->getId();
        }else if(GInOut* v = dynamic_cast<GInOut*>(lines->getVertexB()->getGate())) {
            qInfo() << "INOUT," << v->getVarName();
        }
    }
}

void Diagram::cableIsCreated(GVertex* a, GVertex* b)
{
    if(b->getPosition() == GVertex::LEFT) {
        addCable(a, b);
    }else {
        addCable(b, a);
    }
    qInfo() << m_lines.size();
}

void Diagram::cableIsCliked(GCable *cable)
{
    if (m_cursor->getCursor() == GCursor::QDELETE) {
        deleteCable(cable);
    }
}

void Diagram::gateIsClicked(GGate *gate)
{
    if (m_cursor->getCursor() == GCursor::QDELETE) {
            deleteGate(gate);
    }
}
