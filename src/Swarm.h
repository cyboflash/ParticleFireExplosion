#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

class Swarm {
  private:
    struct Particle *m_pParticles;

  public:
    const static unsigned NPARTICLES = 5000;

  public:
    Swarm();
    ~Swarm();

    const Particle * const getParticles() {return m_pParticles;}
    void update(int elapsedTicks);

};

#endif // SWARM_H_
