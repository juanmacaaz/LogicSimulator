#include "gtext.h"

void GText::focusInEvent(QFocusEvent *event)
{
    m_tmpName = toPlainText();
    QGraphicsItem::focusInEvent(event);
}

void GText::focusOutEvent(QFocusEvent *event)
{
    QString actualName = toPlainText();
    if (actualName.contains(" ") || actualName[0].isDigit() || actualName == "") {
        setPlainText(m_tmpName);
    }else {
        setPlainText(actualName.remove("\n"));
    }
    QGraphicsItem::focusOutEvent(event);
}
