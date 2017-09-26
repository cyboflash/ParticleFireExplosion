#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

class Screen {
  public:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;

    Screen();
    bool init();
    bool processEvents();
    void close();
    void update();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void clear();
    void boxBlur();

  private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_buffer;
    Uint32 *m_buffer2;



};

#endif // SCREEN_H_
