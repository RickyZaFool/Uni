#include "Vector3.h"
#include <cmath>

double LorentzVector::Mod(){
  double mod = sqrt(m_t*m_t - m_pos.Mod()*m_pos.Mod());
  return mod;
}

double T(){
  return m_t
}

void T(double ct){
  m_t = ct;
}

LorentzVector LorentzVector::operator+(LorentzVector b){
  LorentzVector sum;
  sum.T(m_t+b.T());
  return sum
}

