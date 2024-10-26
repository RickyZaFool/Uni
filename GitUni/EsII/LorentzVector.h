#ifndef _LORENTZVECTOR
#define _LORENTZVECTOR
#include "Vector3.h"
#include "Particle.h"
class LorentzVector : public Vector3{
    public:
			LorentzVector(double ct = 0, Vector3 R = 0):m_ct(ct),m_R(R){};
			LorentzVector(double ct, double x, double y, double z):m_ct(ct),m_R(x,y,z){};
			double Mod();
			double T();
			void T(double);
			double X();
			void X(double);
			double Y();
			void Y(double);
			double Z();
			void Z(double);
			Vector3 R();
			void R(Vector3);
			LorentzVector operator+(LorentzVector);
			LorentzVector operator-(LorentzVector);
			double operator*(LorentzVector);
			LorentzVector operator*(double);
			LorentzVector operator/(double);
			LorentzVector operator-();
		private:
			double m_ct;
			Vector3 m_R;
};

LorentzVector operator*(double a, LorentzVector b);
std::ostream& operator<<(std::ostream& output,LorentzVector a);
std::istream& operator>>(std::istream& input, LorentzVector& a);
#endif
