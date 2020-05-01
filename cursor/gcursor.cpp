#include "cursor/gcursor.h"
#include <QDebug>

GCursor::GCursor()
{
    m_currentGate = nullptr;
    m_curretnVertex = 0;
    m_vertex[0] = nullptr;
    m_vertex[1] = nullptr;
    m_gateType = GGate::OR;
    m_cursorMode = CursorMode::BASIC;
}

void GCursor::resetVertex()
{
    m_vertex[0] = nullptr;
    m_curretnVertex = 0;
}

void GCursor::vertexIsClick(GVertex *vertex)
{
    qInfo() << "Cuidado!";
    m_vertex[m_curretnVertex] = vertex;
     if (m_vertex[0] != nullptr){
         if(m_curretnVertex == 0){
             m_curretnVertex++;
         }else {

                 if(m_vertex[0] != m_vertex[1] &&
                     m_vertex[0]->getPosition() != m_vertex[1]->getPosition() &&
                     !m_vertex[0]->getGate()->isEqual(m_vertex[1]->getGate())){
                     m_vertex[m_curretnVertex] = vertex;
                     m_curretnVertex = 0;
                     m_vertex[0]->unSelect();
                     m_vertex[1]->unSelect();
                     emit cableCreated(m_vertex[0], m_vertex[1]);
                 }else {
                     m_curretnVertex = 0;
                     m_vertex[0]->unSelect();
                     m_vertex[1]->unSelect();
                 }
             }
     }
}
