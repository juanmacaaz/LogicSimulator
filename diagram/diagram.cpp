#include "diagram/diagram.h"
#include "QDebug"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

Diagram::Diagram(GCursor* cursor)
{
    m_cursor = cursor;
    m_gates = QList<GGate*>();
    m_lines = QList<GCable*>();
    m_ids = 0;
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
        case GGate::AND: newGate = new GAnd(x, y, getId()); break;
        case GGate::OR:  newGate = new GOr (x, y, getId()); break;
        case GGate::INV: newGate = new GInv(x, y, getId()); break;
        case GGate::XOR: newGate = new GXor(x, y, getId()); break;
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
    if(GInOut* v = dynamic_cast<GInOut*>(gate)) {
        removeItem(v->getText());
    }
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
    bool isValid = true;
    GCable* line = new GCable(a,b);
    if(GInv* v = dynamic_cast<GInv*>(a->getGate())) {
        if(a->getCables().length() > 0){
            isValid = false;
        }
    }
    if(GInv* v = dynamic_cast<GInv*>(b->getGate())) {
        if(b->getCables().length() > 0){
            isValid = false;
        }
    }
    if(GInOut* v = dynamic_cast<GInOut*>(a->getGate())) {
        if (!v->getIOType()){
            if(a->getCables().length() > 0){
                isValid = false;
            }
        }
    }
    if(GInOut* v = dynamic_cast<GInOut*>(b->getGate())) {
        if (!v->getIOType()){
            if(b->getCables().length() > 0){
                isValid = false;
            }
        }
    }
    if(!isInCableList(line)&&isValid) {
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

void Diagram::addInOut(GGate::Element type, int x, int y)
{
    GInOut* newInout;
    if(type == GGate::INPUT) {
        newInout = new GInOut(x, y, true, getId());
        addItem(newInout->getVertexB());
        QObject::connect(newInout->getVertexB(), SIGNAL(vertexClick(GVertex*)), m_cursor, SLOT(vertexIsClick(GVertex*)));
    }else {
        newInout = new GInOut(x, y, false, getId());
        addItem(newInout->getVertexA());
        QObject::connect(newInout->getVertexA(), SIGNAL(vertexClick(GVertex*)), m_cursor, SLOT(vertexIsClick(GVertex*)));
    }
    m_gates.push_back(newInout);
    addItem(newInout);
    newInout->getText()->setFont(QFont("Times", 10, QFont::Bold));
    newInout->getText()->setPlainText(QString::number(newInout->getId()));
    newInout->getText()->setTextInteractionFlags(Qt::TextEditorInteraction);
    addItem(newInout->getText());
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

QString Diagram::generateFunction()
{
    QString dialogMsg = "";
    map<long, string> varNames;
    Conections c;
    for(GCable* lines: m_lines) {
        GGate* a = lines->getVertexA()->getGate();
        GGate* b = lines->getVertexB()->getGate();
        Point left =  getParentInfo(a);
        if(GInOut* v = dynamic_cast<GInOut*>(a)){
            varNames[v->getId()] = v->getText()->toPlainText().toUtf8().constData();
        }
        Point right = getParentInfo(b);
        if(GInOut* v = dynamic_cast<GInOut*>(b)){
             varNames[v->getId()] = v->getText()->toPlainText().toUtf8().constData();
        }
        c.addCable(Cable(Point(left),Point(right)));
    }
    c.setVarNames(varNames);
    for(string s: c.getFunctions()) {
        dialogMsg += QString::fromUtf8(s.c_str()) + "\n";
    }
    return dialogMsg;
}

Point Diagram::getParentInfo(GGate* gate)
{
    if(GAnd* v = dynamic_cast<GAnd*>(gate)) {
        return Point(v->getId(), GGate::AND);
    }else if(GOr* v = dynamic_cast<GOr*>(gate)) {
        return Point(v->getId(), GGate::OR);
    }else if(GXor* v = dynamic_cast<GXor*>(gate)) {
        return Point(v->getId(), GGate::XOR);
    }else if(GInv* v = dynamic_cast<GInv*>(gate)) {
        return Point(v->getId(), GGate::INV);
    }else if(GInOut* v = dynamic_cast<GInOut*>(gate)) {
        if(v->getIOType()) {
            return Point(v->getId(), GGate::INPUT);
        }else {
            return Point(v->getId(), GGate::OUTPUT);
        }
    }else {
        return Point();
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

long Diagram::getId()
{
    return m_ids++;
}
