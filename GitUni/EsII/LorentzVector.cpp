#include "LorentzVector.h"
#include "Vector3.h"

double LorentzVector::Mod(){
  double mod = m_ct*m_ct - m_R.X()*m_R.X() + m_R.Y()*m_R.Y() + m_R.Z()*m_R.Z() ;
  return mod;
}

double LorentzVector::T(){
  return m_ct;
}
void LorentzVector::T(double ct){
  m_ct = ct;
}
double LorentzVector::X(){
  return m_R.X();
}
void LorentzVector::X(double x){
  m_R.X(x);
}
double LorentzVector::Y(){
  return m_R.Y();
}
void LorentzVector::Y(double y){
  m_R.Y(y);
}
double LorentzVector::Z(){
  return m_R.Z();
}
void LorentzVector::Z(double z){
  m_R.Z(z);
}
Vector3 LorentzVector::R(){
  return m_R;
}
void LorentzVector::R(Vector3 r){
  m_R = r;
}
LorentzVector LorentzVector::operator+(LorentzVector b){
  LorentzVector sum;
  sum.T(m_ct+b.T());
  sum.R(m_R+b.R());
  return sum;
}
LorentzVector LorentzVector::operator-(LorentzVector b){
  LorentzVector sum;
  sum.T(m_ct-b.T());
  sum.R(m_R-b.R());
  return sum;
}
double LorentzVector::operator*(LorentzVector b){
  double scalar;
  scalar = m_ct * b.m_ct - m_R.X()*b.m_R.X() - m_R.Y()*b.m_R.Y() - m_R.Z()*b.m_R.Z();
  return scalar; 
}
LorentzVector LorentzVector::operator-(){
  LorentzVector opposite;
  m_ct = -m_ct;
  m_R = -m_R;
  return opposite;
}
LorentzVector LorentzVector::operator*(double a){
  LorentzVector result;
  result.m_ct =  m_ct * a;
  result.m_R = m_R * a;
  return result;
}
LorentzVector LorentzVector::operator/(double a){
  LorentzVector result;
  result = (*this) * (1/a);
  return result;
}
LorentzVector operator*(double a, LorentzVector v){
  LorentzVector result;
  result = v * a;
  return result;
}
std::ostream& operator<<(std::ostream& output, LorentzVector a){
  output << "(" << a.T() << ","<< a.X() << "," << a.Y() << "," << a.Z() << ")";
  return output;
}
std::istream& operator>>(std::istream& input, LorentzVector& a){
  double ct,x,y,z;
  input >> ct >> x >> y >> z;
  a.T(ct); a.X(x); a.Y(y); a.Z(z);
  return input;
}
