#include <iostream>
#include "Swarm.h"

Swarm::Swarm() {
  m_pParticles = new Particle[NPARTICLES];

} // constructor

Swarm::~Swarm() {
  delete [] m_pParticles;

} // destructor

void Swarm::update(int elapsedTicks) {
  for (unsigned i = 0; i < Swarm::NPARTICLES; i++) {
    m_pParticles[i].update(elapsedTicks);
  }

} // update
