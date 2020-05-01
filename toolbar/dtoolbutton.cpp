#include "dtoolbutton.h"

DToolButton::DToolButton(GCursor *cursor, GCursor::CursorMode mode, GGate::Element gateType, QString name, QIcon icon)
{
    m_cursor = cursor;
    m_cursorMode = mode;
    m_gateElement = gateType;
    setIcon(icon);
    setText(name);
    setContextMenuPolicy(Qt::NoContextMenu);
    setContextMenuPolicy(Qt::PreventContextMenu);
    setCheckable(true);
}

void DToolButton::mousePressEvent(QMouseEvent *e)
{
    emit toolButtonClicked();
    m_cursor->setCursorMode(m_cursorMode);
    m_cursor->setGateType(m_gateElement);
    setDown(true);
}
