#include "diagram/ggate.h"

class Point {
  public:
    Point() {}
    Point(int position, GGate::Element element):
      m_element(element),
      m_position(position){};

    GGate::Element getElement() const {return m_element;}
    int getPosition() const {return m_position;}
    void setElement(const GGate::Element element) {m_element = element;}
    void setPosition(const int position) {m_position = position;}

    bool isEqual(const Point &point) const;
    bool operator ==(const Point &point)const;
private:
  GGate::Element m_element;
  int m_position;
};
