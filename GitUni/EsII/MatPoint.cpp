#include "MatPoint.h"
#include "Vector3.h"
#include "Particle.h"
#include <cmath>

Vector3 MatPoint::R(){
  return m_R;
}
void MatPoint::R(Vector3 pos){
  m_R = pos;
}
Vector3 MatPoint::V(){
  return m_V;
}
void MatPoint::V(Vector3 vel){
  m_V = vel;
}
Vector3 MatPoint::GravField(Vector3 point){
  Vector3 r,field;
  r = m_R - point;
  field = (Mass()/pow(r.Mod(), 3)) * r;
  return field;
}
