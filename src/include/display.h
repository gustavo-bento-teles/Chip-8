#pragma once

#include "chip8.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCALE 20
#define WINDOW_WIDTH (WIDTH_CHIP8 * SCALE)
#define WINDOW_HEIGHT (HEIGHT_CHIP8 * SCALE)

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} Display;

bool init_display(Display *display);

void draw_framebuffer(Display *display, bool *framebuffer);

void clear_display(Display *display);

void destroy_display(Display *display);
