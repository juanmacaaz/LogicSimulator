#include "Cable.h"

bool Cable::operator ==(const Cable &p) const {
  return (m_a.isEqual(p.getA())&&m_b.isEqual(p.getB()));
}
