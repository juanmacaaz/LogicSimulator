#include "diagram/diagram.h"

Diagram::Diagram(GCursor* cursor)
{
    m_cursor = cursor;
    m_gates = QList<GGate*>();
    m_lines = QList<GCable*>();
    m_ids = 0;
    setSceneRect(0, 0, 10000, 10000);
    QObject::connect(m_cursor, SIGNAL(cableCreated(GVertex*, GVertex*)), this, SLOT(cableIsCreated(GVertex*,GVertex*)));
}

Diagram::~Diagram()
{
    for (GGate* gate : m_gates)
    {
        delete gate;
    }
    for (GCable* cable : m_lines)
    {
        delete cable;
    }
}

void Diagram::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::LeftButton)
    {
        if(m_cursor->getCursor() == GCursor::GATE)
        {
            addGate(m_cursor->getElement(), mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), getId());
        }
        else if(m_cursor->getCursor() == GCursor::INOUT)
        {
            long id = getId();
            QString name;
            if (m_cursor->getElement() == GGate::INPUT)
            {
                name = nIOName("in");
            }
            else
            {
                name = nIOName("out");
            }
            addInOut(m_cursor->getElement(), mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), id, name);
        }
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

GGate* Diagram::addGate(GGate::Element type, int x, int y, long id)
{
    GGate *newGate;
    switch (type)
    {
    case GGate::AND: newGate = new GAnd(x, y, id); break;
    case GGate::OR:  newGate = new GOr (x, y, id); break;
    case GGate::INV: newGate = new GInv(x, y, id); break;
    case GGate::XOR: newGate = new GXor(x, y, id); break;
    default: newGate = new GGate(0,0,0); break;
    }
    addItem(newGate);
    addItem(newGate->getVertexA());
    addItem(newGate->getVertexB());
    m_gates.push_back(newGate);
    QObject::connect(newGate, SIGNAL(gateClicked(GGate*)), this, SLOT(gateIsClicked(GGate*)));
    QObject::connect(newGate->getVertexA(), SIGNAL(vertexClick(GVertex*)), m_cursor, SLOT(vertexIsClick(GVertex*)));
    QObject::connect(newGate->getVertexB(), SIGNAL(vertexClick(GVertex*)), m_cursor, SLOT(vertexIsClick(GVertex*)));
    return newGate;
}

void Diagram::deleteGate(GGate *gate)
{
    m_gates.removeAll(gate);
    if(GInOut* v = dynamic_cast<GInOut*>(gate))
    {
        removeItem(v->getText());
    }
    if(gate->getVertexA()!=nullptr)
    {
        removeItem(gate->getVertexA());
        for(GCable* cable: gate->getVertexA()->getCables())
        {
            deleteCable(cable);
        }
    }
    if(gate->getVertexB()!=nullptr)
    {
        removeItem(gate->getVertexB());
        for(GCable* cable: gate->getVertexB()->getCables())
        {
            deleteCable(cable);
        }
    }
    m_cursor->resetVertex();
    for (GGate* gate : m_gates)
        gate->disActiveVertex();
    removeItem(gate);
    delete gate;
}

void Diagram::addCable(GVertex* a, GVertex* b)
{
    bool isValid = true;
    GCable* line = new GCable(a,b);
    if(dynamic_cast<GInv*>(b->getGate()))
    {
        if(b->getCables().length() > 0)
        {
            isValid = false;
        }
    }
    if(dynamic_cast<GOut*>(a->getGate()))
    {
        if(a->getCables().length() > 0)
        {
            isValid = false;
        }
    }
    if(dynamic_cast<GOut*>(b->getGate()))
    {
        if(b->getCables().length() > 0)
        {
            isValid = false;
        }
    }
    if(!isInCableList(line) && isValid)
    {
        a->addCable(line);
        b->addCable(line);
        m_lines.push_back(line);
        addItem(line);
        QObject::connect(line, SIGNAL(cableClick(GCable*)), this, SLOT(cableIsCliked(GCable*)));
        realtimeSimulate();
    }
}

void Diagram::deleteCable(GCable* cable)
{
    removeItem(cable);
    cable->getVertexA()->removeCable(cable);
    cable->getVertexB()->removeCable(cable);
    m_lines.removeAll(cable);
    delete cable;
    realtimeSimulate();
}

GInOut* Diagram::addInOut(GGate::Element type, int x, int y, long id, const QString& name)
{
    GInOut* newInout;

    if(type == GGate::INPUT)
    {
        newInout = new GIn(x, y, id);
        addItem(newInout->getVertexB());
        QObject::connect(newInout->getVertexB(), SIGNAL(vertexClick(GVertex*)), m_cursor, SLOT(vertexIsClick(GVertex*)));
    }
    else
    {
        newInout = new GOut(x, y, id);
        addItem(newInout->getVertexA());
        QObject::connect(newInout->getVertexA(), SIGNAL(vertexClick(GVertex*)), m_cursor, SLOT(vertexIsClick(GVertex*)));
    }

    m_gates.push_back(newInout);
    addItem(newInout);
    newInout->getText()->setFont(QFont("Times", 11, QFont::Bold));
    newInout->getText()->setPlainText(name);
    newInout->getText()->setTextInteractionFlags(Qt::TextEditorInteraction);
    addItem(newInout->getText());
    QObject::connect(newInout, SIGNAL(gateClicked(GGate*)), this, SLOT(gateIsClicked(GGate*)));
    QObject::connect(newInout->getText(), SIGNAL(nameChange(const QString&, bool&)), this, SLOT(nameChange(const QString&, bool&)));
    return newInout;
}

bool Diagram::isInCableList(GCable *cable)
{
    for(GCable* line: m_lines)
    {
        if(line->isEqual(cable))
            return true;
    }
    return false;
}

void Diagram::realtimeSimulate()
{
    QString msg = "";
    Operation * func;
    QStringList sub_expr;
    QStringList expr = (generateFunction()).split('\n');
    expr.removeLast();
    for (GGate* gate : m_gates)
    {
        if(GOut* v = dynamic_cast<GOut*>(gate))
        {
            v->disActive();
        }
    }
    for (QString e : expr)
    {
        msg = "";
        sub_expr = e.split('=');

        if (sub_expr.length() >= 2)
        {
            string s_func = sub_expr[1].toStdString();

            quitSpaces(&s_func);
            func = parse(s_func);

            msg += sub_expr[0] + " = ";

            if (func->eval(getInValues()))
                msg += '1';
            else
                msg += '0';
        }
        for (GGate* gate : m_gates)
        {
            if(GOut* v = dynamic_cast<GOut*>(gate))
            {
                QString txt  = v->getText()->toPlainText();
                QString txt2 = msg.remove(" ").split("=")[0];
                QString txt3 = msg.remove(" ").split("=")[1];
                if (txt == txt2)
                {
                    if(txt3 == "1") {
                        v->active();
                    }
                }
            }
        }
    }

}

QString Diagram::generateFunction()
{
    QString dialogMsg = "";
    map<long, string> varNames;
    Conections c;

    for(GCable* lines: m_lines)
    {
        GGate* a = lines->getVertexA()->getGate();
        GGate* b = lines->getVertexB()->getGate();
        Point left =  getParentInfo(a);
        Point right = getParentInfo(b);


        if(GIn* v = dynamic_cast<GIn*>(a))
            varNames[v->getId()] = v->getText()->toPlainText().toUtf8().constData();
        else if(GIn* v = dynamic_cast<GIn*>(b))
            varNames[v->getId()] = v->getText()->toPlainText().toUtf8().constData();

        if(GOut* v = dynamic_cast<GOut*>(a))
        {
            varNames[v->getId()] = v->getText()->toPlainText().toUtf8().constData();
        }
        else if(GOut* v = dynamic_cast<GOut*>(b))
        {
             varNames[v->getId()] = v->getText()->toPlainText().toUtf8().constData();
        }
        c.addCable(Cable(Point(left),Point(right)));
    }
    c.setVarNames(varNames);
    for (string s: c.getFunctions())
            dialogMsg += QString::fromUtf8(s.c_str()) + "\n";

    return dialogMsg;
}

unordered_map<string,bool> Diagram::getInValues()
{
    unordered_map<string,bool> env;
    for (GGate* g: m_gates)
        if(GIn* v = dynamic_cast<GIn*>(g))
            env[(v->getText())->toPlainText().toStdString()] = v->isActive();

    return env;
}

void Diagram::nameChange(const QString &varName, bool &repited)
{
    int repitedTimes = 0;
    for (GGate* gate : m_gates)
    {
        if(GInOut* v = dynamic_cast<GInOut*>(gate))
        {
            if (v->getText()->toPlainText() == varName)
            {
                repitedTimes++;
            }
        }
    }
    if(repitedTimes < 2)
        repited = false;
    else
        repited = true;
}


Point Diagram::getParentInfo(GGate* gate)
{
    if(GAnd* v = dynamic_cast<GAnd*>(gate))
    {
        return Point(v->getId(), GGate::AND);
    }
    else if(GOr* v = dynamic_cast<GOr*>(gate))
    {
        return Point(v->getId(), GGate::OR);
    }
    else if(GXor* v = dynamic_cast<GXor*>(gate))
    {
        return Point(v->getId(), GGate::XOR);
    }
    else if(GInv* v = dynamic_cast<GInv*>(gate))
    {
        return Point(v->getId(), GGate::INV);
    }
    else if(GOut* v = dynamic_cast<GOut*>(gate))
    {
        return Point(v->getId(), GGate::OUTPUT);
    }
    else if(GIn* v = dynamic_cast<GIn*>(gate))
    {
        return Point(v->getId(), GGate::INPUT);
    }
    else
    {
        return Point();
    }
}

void Diagram::cableIsCreated(GVertex* a, GVertex* b)
{
    if(b->getPosition() == GVertex::LEFT)
    {
        addCable(a, b);
    }
    else
    {
        addCable(b, a);
    }
}

void Diagram::cableIsCliked(GCable *cable)
{
    if (m_cursor->getCursor() == GCursor::QDELETE)
    {
        deleteCable(cable);
    }
}

void Diagram::gateIsClicked(GGate *gate)
{
    if (m_cursor->getCursor() == GCursor::QDELETE)
    {
            deleteGate(gate);
    }
    else if (m_cursor->getCursor() == GCursor::CHANGE)
    {
        if (GIn* v = dynamic_cast<GIn*>(gate))
        {
            if (v->isActive())
            {
                v->disActive();
            }
            else
            {
                v->active();
            }
        }
        realtimeSimulate();
    }
    update(0,0,width(),height());
}

long Diagram::getId()
{
    return m_ids++;
}

QString Diagram::nIOName(const QString& io)
{
    if(m_gates.length() == 0)
    {
        return QString(io+"0");
    }
    QString name;
    bool found = false;
    int i = 0;
    while (!found)
    {
        name = io + QString::number(i);
        bool exist = false;
        for (GGate* gate: m_gates)
        {
            if (GInOut* g = dynamic_cast<GInOut*>(gate))
            {
                if (g->getText()->toPlainText() == name)
                {
                    exist = true;
                }
            }
        }
        if(!exist)
            found = true;
        i++;
    }
    return name;
}

QString Diagram::saveDiagram()
{
    QString binary;
    for (GGate* gate: m_gates)
    {
        if (dynamic_cast<GAnd*>(gate))
        {
            binary += "AND";
        }
        else if(dynamic_cast<GOr*>(gate))
        {
            binary += "OR";
        }
        else if(dynamic_cast<GInv*>(gate))
        {
            binary += "INV";
        }
        else if(dynamic_cast<GXor*>(gate))
        {
            binary += "XOR";
        }
        else if(GIn* v = dynamic_cast<GIn*>(gate))
        {
            binary += "IN " + v->getText()->toPlainText() + " " + QString::number(v->isActive());
        }
        else if(GOut* v = dynamic_cast<GOut*>(gate))
        {
            binary += "OUT " + v->getText()->toPlainText();
        }
        binary += " " + QString::number(gate->getId()) + " " + QString::number(gate->x()+70) + " " + QString::number(gate->y()+40) + "\n";
    }
    for (GCable* cable : m_lines)
    {
        binary+= "CABLE " +  QString::number(cable->getVertexA()->getGate()->getId()) +
                " " + QString::number(cable->getVertexB()->getGate()->getId()) + "\n";
    }
    binary+=QString::number(getId());
    return binary;
}

void Diagram::loadDiagram(QString binary)
{
    QMap<long, GGate*> tmpGates;
    QStringList lines = binary.split("\n");

    for(QString line : lines)
    {
        QStringList field = line.split(" ");
        if (field[0] == "CABLE")
        {
            addCable(tmpGates[field[1].toLong()]->getVertexB() ,tmpGates[field[2].toLong()]->getVertexA());
        }
        else if (field[0] == "IN")
        {
            tmpGates[field[3].toLong()] = addInOut(GGate::INPUT, field[4].toInt(), field[5].toInt(), field[3].toLong(), field[1]);
        }
        else if (field[0] == "OUT")
        {
            tmpGates[field[2].toLong()] = addInOut(GGate::OUTPUT, field[3].toInt(), field[4].toInt(), field[2].toLong(), field[1]);
        }
        else if (field[0] == "AND")
        {
            tmpGates[field[1].toLong()] = addGate(GGate::AND, field[2].toInt(), field[3].toInt(), field[1].toLong());
        }
        else if (field[0] == "INV")
        {
            tmpGates[field[1].toLong()] = addGate(GGate::INV, field[2].toInt(), field[3].toInt(), field[1].toLong());
        }
        else if (field[0] == "OR")
        {
            tmpGates[field[1].toLong()] = addGate(GGate::OR, field[2].toInt(), field[3].toInt(), field[1].toLong());
        }
        else if (field[0] == "XOR")
        {
           tmpGates[field[1].toLong()] = addGate(GGate::XOR, field[2].toInt(), field[3].toInt(), field[1].toLong());
        }
        else
        {
            m_ids = line.toLong();
        }
    }
}
