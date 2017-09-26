#include <iostream>
#include <math.h>
#include <SDL.h>
#include <stdlib.h>
#include <time.h>

#include "Screen.h"
#include "Swarm.h"

using namespace std;

int main(int argc, char **argv) {

  srand(time(NULL));

  Screen screen;

  if(!screen.init()) {
    cout << "Error initializing SDL" << endl;
  }

  Swarm swarm;

  // Game Loop
  const Particle * const pParticles = swarm.getParticles();
  while(true) {
    // update partciles

    // draw particles
    int elapsedTicks = SDL_GetTicks();

    // screen.clear();
    swarm.update(elapsedTicks);

    Uint8 red = (1 + sin(elapsedTicks*0.0001))/2 * 256;
    Uint8 green = (1 + sin(elapsedTicks*0.0007))/2 * 256;
    Uint8 blue = (1 + sin(elapsedTicks*0.0005))/2 * 256;

    for(unsigned i = 0; i < Swarm::NPARTICLES; i++) {
      Particle particle = pParticles[i];
      unsigned x = (particle.m_x + 1) * 0.5*Screen::SCREEN_WIDTH;
      unsigned y = particle.m_y * 0.5*Screen::SCREEN_WIDTH +
        0.5*Screen::SCREEN_HEIGHT;

      screen.setPixel(x, y, red, green, blue);
    }

    screen.boxBlur();
    // screen.update();

    // draw the screen
    screen.update();

    // check for messages/events
    if (!screen.processEvents())
      break;

  }

  screen.close();

  return 0;
}
