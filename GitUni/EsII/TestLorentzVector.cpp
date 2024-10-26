#include <iostream>
#include "LorentzVector.h"

using namespace std;


int main(){

  /*LorentzVector a, b;
  Vector3 v(1,2,3), w(5,3,2);
  a.T(0);
  b.T(1);
  a.R(v);
  b.R(w);*/
  Vector3 v(4,5,6);

  LorentzVector a(0,1,2,3);
  LorentzVector b(1,v);
  LorentzVector c;

  cout << "null tetravector: " << c<< endl;
  cout << "a = " << a << ", b = " << b  << endl;
  cout << "square mod of a " << a.Mod() << endl;
  cout << "a + b = " << a + b << endl;
  cout << "a - b = " << a - b << endl;
  cout << "2a = " << 2 * a << endl;
  cout << "b * 3 = " << b * 3 << endl;
  cout << "a * b = " << a * b << endl;
  

  return 0;
}