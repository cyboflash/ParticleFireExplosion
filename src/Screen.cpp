#include <iostream>
#include <stdexcept>

#include "Screen.h"

Screen::Screen():
  m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL),
  m_buffer2(NULL)
{

}

bool Screen::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    return false;
  }

  m_window = SDL_CreateWindow(
      "Particle Fire Explosion",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN
      );

  if (NULL == m_window) {
    SDL_Quit();
    return false;
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
  if (NULL == m_renderer) {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  m_texture = SDL_CreateTexture(
      m_renderer,
      SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_STATIC,
      SCREEN_WIDTH,
      SCREEN_HEIGHT
      );

  if (NULL == m_texture) {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  try
  {
    m_buffer = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
    m_buffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
  }
  catch (std::bad_alloc)
  {
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
  memset(m_buffer2, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));

  return true;
}

void Screen::boxBlur() {
  Uint32 *pTmp;
  pTmp      = m_buffer;
  m_buffer  = m_buffer2;
  m_buffer2 = pTmp;

  for (auto y = 0; y < SCREEN_HEIGHT; y++) {
    for (auto x = 0; x < SCREEN_WIDTH; x++) {
      //  Take average of the pixels around a given pixel
      auto totalRed   = 0;
      auto totalGreen = 0;
      auto totalBlue  = 0;

      for (auto col = -1; col <= 1; col++) {
        for (auto row = -1; row <= 1; row++) {
          auto pixelX = x + row;
          auto pixelY = y + col;

          // check we don't go beyond the screen
          if ((pixelX < 0) || (pixelX >= SCREEN_WIDTH) ||
              (pixelY < 0) || (pixelY >= SCREEN_HEIGHT)) {
            continue;
          }

          Uint32 color = m_buffer2[pixelY*SCREEN_WIDTH + pixelX];

          totalRed   += (color >> 24) & 0xff;
          totalGreen += (color >> 16) & 0xff;
          totalBlue  += (color >>  8) & 0xff;
        } // for (row)
      } // for (col)

      Uint8 red = totalRed/9;
      Uint8 green = totalGreen/9;
      Uint8 blue = totalBlue/9;
      setPixel(x, y, red, green, blue);

    } // for (int x)
  } // for (int y)

} // Screen::boxBlur

void Screen::clear() {
  memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
  memset(m_buffer2, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
}

void Screen::update() {
  SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH*sizeof(Uint32));
  SDL_RenderClear(m_renderer);
  SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
  SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
  {
    return;
  }

  Uint32 color;

  color = red;
  color <<= 8;
  color += green;
  color <<= 8;
  color += blue;
  color <<= 8;
  color += 0xff;
  m_buffer[y*SCREEN_WIDTH + x] = color;

} // setPixel

bool Screen::processEvents() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if (SDL_QUIT == event.type) {
      return false;
    }
  }
  return true;
}

void Screen::close() {
  delete [] m_buffer;
  delete [] m_buffer2;
  SDL_DestroyTexture(m_texture);
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();

}
