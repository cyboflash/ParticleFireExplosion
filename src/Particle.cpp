#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "Particle.h"

Particle::Particle() {
  init();
} // constructor

void Particle::init() {
  m_x = 0;
  m_y = 0;
  m_direction = 2*M_PI*(1.0*rand()/RAND_MAX); // angle
  m_speed = (0.035*rand())/RAND_MAX;
  m_speed *=m_speed;
}

Particle::~Particle() {
} // destructor

void Particle::update(int elapsedTicks) {
  int interval = elapsedTicks - m_lastTick;

  m_direction += interval*0.0002;

  double xspeed = m_speed * cos(m_direction);
  double yspeed = m_speed * sin(m_direction);
  m_lastTick = elapsedTicks;
  m_x += xspeed*interval;
  m_y += yspeed*interval;

  if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1)
    init();

  if (rand() < RAND_MAX/150)
    init();
}
