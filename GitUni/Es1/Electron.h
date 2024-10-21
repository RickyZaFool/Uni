#ifndef _ELECTRON
#define _ELECTRON
#include "Particle.h"


class Electron : public Particle{
 public:
  Electron():Particle(9.1e-31, 1.6e-19){}
};

#endif
