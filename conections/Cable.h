#include "conections/Point.h"

class Cable {
  private:
    Point m_a;
    Point m_b;
  public:
    Cable() {};
    Cable(Point a, Point b): m_a(a), m_b(b) {};
    Point getA() const {return m_a;}
    Point getB() const {return m_b;}
    void setA(const Point a) {m_a = a;}
    void setB(const Point b) {m_b = b;}
    bool operator ==(const Cable &p) const;
};
