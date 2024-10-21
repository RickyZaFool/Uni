#ifndef _PARTICLE
#define _PARTICLE
#include <string>
class Particle{
 public:
  Particle(double mass=0, double charge=0, std::string name = ""):m_mass(mass),m_charge(charge),m_name(name){}
  double Mass() {return  m_mass;}
  double Charge(){return m_charge;}
  void Mass(double m){m_mass = m;}
  void Charge(double q){m_charge = q;}
  std::string Name(){return m_name;}
  void Name(std::string n){m_name = n;}
 private:
  double m_mass;
  double m_charge;
  std::string m_name;
};



#endif
