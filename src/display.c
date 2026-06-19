#include "include/display.h"
#include "include/chip8.h"

bool init_display(Display *display) {
  display->window = NULL;
  display->renderer = NULL;

  SDL_SetMainReady();

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Falha ao inicializar o subsistema de vídeo!",
                             NULL);
    return false;
  }

  display->window =
      SDL_CreateWindow("Chip-8 Emulator", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  if (!display->window) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Falha ao criar janela!", NULL);

    destroy_display(display);
    return false;
  }

  display->renderer =
      SDL_CreateRenderer(display->window, -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!display->renderer) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Falha ao criar renderer!", NULL);
    destroy_display(display);
    return false;
  }

  return true;
}

void draw_framebuffer(Display *display, bool *framebuffer) {
  SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
  SDL_RenderClear(display->renderer);

  SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);

  for (int i = 0; i < WIDTH_CHIP8 * HEIGHT_CHIP8; i++) {
    if (framebuffer[i]) {
      int px = (i % WIDTH_CHIP8) * SCALE;
      int py = (i / WIDTH_CHIP8) * SCALE;

      SDL_Rect rect = {px, py, SCALE, SCALE};
      SDL_RenderFillRect(display->renderer, &rect);
    }
  }

  SDL_RenderPresent(display->renderer);
}

void destroy_display(Display *display) {

  SDL_DestroyRenderer(display->renderer);

  SDL_DestroyWindow(display->window);

  SDL_Quit();
}
