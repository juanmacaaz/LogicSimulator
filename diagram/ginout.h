#ifndef GINPUT_H
#define GINPUT_H

#include <QString>
#include "ggate.h"

class GInOut: public GGate
{
public:
    GInOut(int x, int y, bool isInput, QString varName):GGate(x, y) {
        m_varName = varName;
        if(isInput) {
            m_element = GGate::INPUT;
            setPixmap(QPixmap(QDir().absolutePath()+"/img/input.png"));
        }else {
            m_element = GGate::OUTPUT;
            setPixmap(QPixmap(QDir().absolutePath()+"/img/output.png"));
        }
    }
    QString getVarName() { return m_varName;};
private:
    QString m_varName;
    GGate::Element m_element;
};

#endif // GINPUT_H
