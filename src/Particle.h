#ifndef PARTICLE_H_
#define PARTICLE_H_

struct Particle {
  double m_x;
  double m_y;
  double m_direction;
  double m_speed;
  int m_lastTick;

  Particle();
  ~Particle();
  void init();

  void update(int elapsedTicks);

};

#endif // PARTICLE_H_
