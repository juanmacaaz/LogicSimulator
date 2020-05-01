#ifndef GOR_H
#define GOR_H

#include "diagram/ggate.h"

class GOr : public GGate
{
public:
    GOr(int x, int y, int id);
    long getId() { return m_id;};
private:
    long m_id;
};

#endif // GOR_H
