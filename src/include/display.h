#pragma once

#include "chip8.h"
#include <SDL2/SDL.h>

#define SCALE 10
#define WINDOW_WIDTH (WIDTH_CHIP8 * SCALE)
#define WINDOW_HEIGHT (HEIGHT_CHIP8 * SCALE)

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} Display;

void init_display(Display *display);

void draw_framebuffer(bool *framebuffer);
