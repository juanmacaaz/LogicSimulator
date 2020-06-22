#ifndef GIN_H
#define GIN_H

#include "ginout.h"

class GIn : public GInOut
{
public:
    GIn(int x,int y, long id);
    bool isActive() const {return m_active;}
    void active();
    void disActive();
private:
    bool m_active;
};



#endif // GIN_H
