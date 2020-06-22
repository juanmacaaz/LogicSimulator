#ifndef GOUT_H
#define GOUT_H

#include "ginout.h"

class GOut : public GInOut
{
private:
    bool m_active;
public:
    GOut(int x,int y, long id);
    bool isActive() const {return m_active;}
    void active();
    void disActive();
};

#endif // GOUT_H
