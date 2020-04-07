#ifndef GINPUT_H
#define GINPUT_H

#include <QString>
#include "ggate.h"

class GInOut: public GGate
{
public:
    GInOut(int x, int y, bool isInput, long varName):GGate(x, y) {
        m_isInput = isInput;
        m_varName = varName;
        if(isInput) {
            m_element = GGate::INPUT;
            setPixmap(QPixmap(QDir().absolutePath()+"/img/input.png"));
        }else {
            m_element = GGate::OUTPUT;
            setPixmap(QPixmap(QDir().absolutePath()+"/img/output.png"));
        }
    }
    long getVarName() { return m_varName;};
    bool getIOType() {return m_isInput;}
private:
    bool m_isInput;
    long m_varName;
    GGate::Element m_element;
};

#endif // GINPUT_H
