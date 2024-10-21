#ifndef _MATPOINT
#define _MATPOINT
#include "Vector3.h"
#include "Particle.h"
#include <string>
class MatPoint : public Particle{
 public:
  MatPoint(Particle particle = Particle(), Vector3 R= Vector3(), Vector3 V= Vector3()):Particle(particle),m_R(R),m_V(V){};
  MatPoint(double mass = 0, double charge = 0, Vector3 R= Vector3(), Vector3 V= Vector3()):Particle(mass, charge),m_R(R),m_V(V){};
  MatPoint(double mass = 0, double charge = 0, std::string name ="",  Vector3 R= Vector3(), Vector3 V= Vector3()):Particle(mass, charge,name),m_R(R),m_V(V){};
  Vector3 R();
  Vector3 V();
  void R(Vector3);
  void V(Vector3);
  Vector3 GravField(Vector3);
private:
  Vector3 m_R;
  Vector3 m_V;
};


#endif
