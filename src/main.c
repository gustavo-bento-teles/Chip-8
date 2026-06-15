#include "input.h"
#define SDL_MAIN_HANDLED
#include "include/chip8.h"
#include "include/display.h"
#include "include/input.h"
#include "include/rom.h"
#include <stdbool.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Nenhuma ROM fornecida!", NULL);

    return 1;
  }

  Chip8 *chip8 = calloc(1, sizeof(Chip8));
  Display *display = calloc(1, sizeof(Display));

  if (!chip8) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Falha ao criar o emulador!", NULL);
    return 1;
  }

  if (!display) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Falha ao criar o sistema de vídeo!", NULL);
    return 1;
  }

  chip8_init(chip8);

  if (!load_rom(argv[1], chip8->memory, MEMORY_INIT_POINT)) {
    return 1;
  }

  if (!init_display(display)) {
    return 1;
  }

  SDL_Event event;

  bool running = true;

  while (running) {

    while (SDL_PollEvent(&event)) {

      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

    update_keyboard(chip8->keypad, keyboard);

    chip8_fetch(chip8);

    if (!chip8_execute(chip8)) {
      break;
    }

    clear_display(display);
    draw_framebuffer(display, chip8->framebuffer);

    SDL_Delay(16);
  }

  destroy_display(display);

  free(chip8);
  free(display);

  return 0;
}
