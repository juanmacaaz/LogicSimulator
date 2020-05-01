#ifndef DTOOLBUTTON_H
#define DTOOLBUTTON_H

#include <QToolButton>
#include "cursor/gcursor.h"
class DToolButton: public QToolButton
{
    Q_OBJECT
public:
    DToolButton(GCursor* cursor, GCursor::CursorMode mode, GGate::Element gateType ,QString name, QIcon icon);
private:
    GCursor* m_cursor;
    GCursor::CursorMode m_cursorMode;
    GGate::Element m_gateElement;
    void mousePressEvent(QMouseEvent *e);
signals:
    void toolButtonClicked();
};

#endif // DTOOLBUTTON_H
