#include "Vector3.h"
#include "OdeSolver.h"
#include <cmath>

void OdeSolver::AddMatPoint(MatPoint tmp){
  m_p.push_back(tmp);
}

vector<MatPoint> OdeSolver::GetMatPoints(){
  return m_p;
}

MatPoint OdeSolver::GetMatPoint(unsigned int i){
  return m_p[i];
}

unsigned int OdeSolver::N(){
  return m_p.size();
}

void OdeSolver::T(double t0){
  m_t=t0;
}

double OdeSolver::T(){
  return      m_t;
}

void OdeSolver::DeltaT(double h){
  m_h = h;
}

double OdeSolver::DeltaT(){
  return   m_h;
}


Vector3 OdeSolver::m_A(unsigned int i, double t, vector<MatPoint> p){
  //STEP 3 Calcolo dell'accelerazione dovuta a forze interne e forze esterne
  // * Sommo le forze interne dovute a tutti i MatPoint con indice j diverso da i
  Vector3 totalForce;
  for(unsigned int j = 0; j < p.size(); j++){
    if(j != i){
      totalForce = totalForce + fInternal(i,j,t,p);
    }
  }
  totalForce = totalForce + fExternal(i,t,p);
  // * Ritorno l'accelerazione
  return totalForce * (1/p[i].Mass());
}

//Da implementare a cura dello studente
void OdeSolver::Step(){

  if (m_method=="Eulero"){
    vector<Vector3>  k1(m_p.size());
    vector<Vector3>  w1(m_p.size());
    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h * m_p[i].V();
      w1[i] = m_h * m_A(i,m_t,m_p);
    }

    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k1[i]);
      m_p[i].V(m_p[i].V() +  w1[i]);
    }

  } else if (m_method=="Rk2"){
    vector<Vector3>  k1(m_p.size());
    vector<Vector3>  w1(m_p.size());
    vector<Vector3>  k2(m_p.size());
    vector<Vector3>  w2(m_p.size());
    vector<MatPoint> p_temp(m_p);

    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h * m_p[i].V();
      w1[i] = m_h * m_A(i,m_t,m_p);
    }

    
    for (unsigned int i=0;i<m_p.size();i++){
      p_temp[i].R(m_p[i].R() + k1[i]*(0.5));
      p_temp[i].V(m_p[i].V() + w1[i]*(0.5));
    }

    for (unsigned int i=0;i<m_p.size();i++){
      k2[i] = m_h * p_temp[i].V();
      w2[i] = m_h * m_A(i,m_t,p_temp);
    }
    
    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k2[i]);
      m_p[i].V(m_p[i].V() + w2[i]);
    }
    
    // STEP 5 implementare Runge Kutta al secondo ordine
    // * Riprendere il calcolo di k1/w1
    // * Per il calcolo di k2/w2 devo dotarmi di una copia di m_p
    //   calcolata nel punto intermedio dell'intervallo temporale
  }
  m_t += m_h;
  
}

