#include "Point.h"

bool Point::isEqual(const Point &point) const{
  return point.getElement() == m_element && m_position == point.getPosition();
}

bool Point::operator ==(const Point &point)const {
  return isEqual(point);
}