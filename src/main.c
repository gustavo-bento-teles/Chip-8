#include "include/chip8.h"

#include <stdlib.h>

int main() {
  Chip8 *chip8 = calloc(1, sizeof(Chip8));

  if (!chip8) {
    return 1;
  }

  free(chip8);

  return 0;
}
