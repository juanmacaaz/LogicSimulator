#include "diagramtoolbar.h"

DiagramToolBar::DiagramToolBar(GCursor *cursor)
{
    setContextMenuPolicy(Qt::NoContextMenu);
    setContextMenuPolicy(Qt::PreventContextMenu);
    m_toolButtons.push_back(new DToolButton(cursor,
                                  GCursor::BASIC,
                                  GGate::AND,
                                  "Basic",
                                  QIcon(QDir().absolutePath()+"/img/cursor.png")));
    m_toolButtons.push_back(new DToolButton(cursor,
                                 GCursor::QDELETE, GGate::AND,
                                 "Delete",
                                 QIcon(QDir().absolutePath()+"/img/delete.png")));
    m_toolButtons.push_back(new DToolButton(cursor,
                                 GCursor::CHANGE,
                                 GGate::AND,
                                 "Change",
                                 QIcon(QDir().absolutePath()+"/img/circle.png")));
    m_toolButtons.push_back(new DToolButton(cursor,
                                 GCursor::GATE,
                                 GGate::OR,
                                 "OR Gate",
                                 QIcon(QDir().absolutePath()+"/img/or.png")));
    m_toolButtons.push_back(new DToolButton(cursor,
                                 GCursor::GATE,
                                 GGate::XOR,
                                 "XOR Gate",
                                 QIcon(QDir().absolutePath()+"/img/xor.png")));
    m_toolButtons.push_back(new DToolButton(cursor,
                                 GCursor::GATE,
                                 GGate::INV,
                                 "INV Gate",
                                 QIcon(QDir().absolutePath()+"/img/inv.png")));
    m_toolButtons.push_back(new DToolButton(cursor,
                                 GCursor::GATE,
                                 GGate::AND,
                                 "AND Gate",
                                 QIcon(QDir().absolutePath()+"/img/and.png")));
    m_toolButtons.push_back(new DToolButton(cursor,
                                 GCursor::INOUT,
                                 GGate::INPUT,
                                 "Input Gate",
                                 QIcon(QDir().absolutePath()+"/img/inputE.png")));
    m_toolButtons.push_back(new DToolButton(cursor,
                                 GCursor::INOUT,
                                 GGate::OUTPUT,
                                 "Output Gate",
                                 QIcon(QDir().absolutePath()+"/img/output.png")));
    for (DToolButton* button : m_toolButtons)
    {
        addWidget(button);
        QObject::connect(button, SIGNAL(toolButtonClicked()), this, SLOT(toolButtonClicked()));
    }
}

void DiagramToolBar::toolButtonClicked()
{
    for (DToolButton* button : m_toolButtons)
    {
           button->setChecked(false);
    }
}
