#include "include/chip8.h"
#include "include/display.h"

#include <stdlib.h>

int main() {
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

  if (!init_display(display)) {
    return 1;
  }

  free(chip8);
  free(display);

  return 0;
}
