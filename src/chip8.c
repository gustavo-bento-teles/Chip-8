#include "include/chip8.h"

#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

void chip8_init(Chip8 *chip8) {
  chip8->pc = MEMORY_INIT_POINT;
  srand(time(NULL));
}

void chip8_fetch(Chip8 *chip8) {
  uint8_t first_byte = chip8->memory[chip8->pc];
  uint8_t second_byte = chip8->memory[chip8->pc + 1];

  chip8->opcode = (first_byte << 8) | second_byte;
}

bool chip8_execute(Chip8 *chip8) {

  switch (chip8->opcode & 0xF000) {

  case 0x0000: {
    switch (chip8->opcode) {

    case 0x00E0:
      memset(chip8->framebuffer, false, sizeof(chip8->framebuffer));
      break;

    case 0x00EE:
      if (chip8->sp == 0) {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR, "Erro",
            "Impossível retornar quando stack pointer é igual a 0!", NULL);
        return false;
        break;
      }

      chip8->pc = chip8->stack[--chip8->sp];
      return true;
    }
    break;
  }

  case 0x1000: {
    uint16_t nnn = chip8->opcode & 0x0FFF;
    chip8->pc = nnn;
    return true;
  }

  case 0x2000: {
    uint16_t nnn = chip8->opcode & 0x0FFF;

    if (chip8->sp >= STACK_SIZE) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                               "Impossível chamar função quando stack pointer "
                               "é igual ou maior do que tamanho da stack!",
                               NULL);
      return false;
      break;
    }

    chip8->stack[chip8->sp++] = chip8->pc + 2;
    chip8->pc = nnn;
    return true;
  }

  case 0x3000: {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->opcode & 0x00FF;

    if (chip8->v[x] == nn) {
      chip8->pc += 2;
    }
    break;
  }

  case 0x4000: {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->opcode & 0x00FF;

    if (chip8->v[x] != nn) {
      chip8->pc += 2;
    }
    break;
  }

  case 0x5000: {
    if ((chip8->opcode & 0x000F) == 0x0) {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;
      uint8_t y = (chip8->opcode & 0x00F0) >> 4;

      if (chip8->v[x] == chip8->v[y]) {
        chip8->pc += 2;
      }
      break;
    }

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Opcode desconhecido!", NULL);
    return false;
  }

  case 0x6000: {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->opcode & 0x00FF;

    chip8->v[x] = nn;
    break;
  }

  case 0x7000: {
    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->opcode & 0x00FF;

    chip8->v[x] += nn;
    break;
  }

  case 0x8000: {
    switch (chip8->opcode & 0x000F) {
    case 0x0: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;
      uint8_t y = (chip8->opcode & 0x00F0) >> 4;

      chip8->v[x] = chip8->v[y];
      break;
    }

    case 0x1: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;
      uint8_t y = (chip8->opcode & 0x00F0) >> 4;

      chip8->v[x] |= chip8->v[y];
      break;
    }

    case 0x2: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;
      uint8_t y = (chip8->opcode & 0x00F0) >> 4;

      chip8->v[x] &= chip8->v[y];
      break;
    }

    case 0x3: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;
      uint8_t y = (chip8->opcode & 0x00F0) >> 4;

      chip8->v[x] ^= chip8->v[y];
      break;
    }

    case 0x4: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;
      uint8_t y = (chip8->opcode & 0x00F0) >> 4;

      uint16_t sum = chip8->v[x] + chip8->v[y];

      chip8->v[0xF] = (sum > 0xFF);
      chip8->v[x] = (uint8_t)sum;

      break;
    }

    case 0x5: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;
      uint8_t y = (chip8->opcode & 0x00F0) >> 4;

      chip8->v[0xF] = (chip8->v[x] > chip8->v[y]);
      chip8->v[x] = chip8->v[x] - chip8->v[y];

      break;
    }

    case 0x6: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;

      chip8->v[0xF] = chip8->v[x] & 0x1;
      chip8->v[x] >>= 1;

      break;
    }

    case 0x7: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;
      uint8_t y = (chip8->opcode & 0x00F0) >> 4;

      chip8->v[0xF] = (chip8->v[y] > chip8->v[x]);
      chip8->v[x] = chip8->v[y] - chip8->v[x];

      break;
    }

    case 0xE: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;

      chip8->v[0xF] = (chip8->v[x] >> 7) & 0x1;
      chip8->v[x] <<= 1;
      break;
    }
    }
    break;
  }

  case 0x9000: {
    if ((chip8->opcode & 0x000F) & 0x0) {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;
      uint8_t y = (chip8->opcode & 0x00F0) >> 4;

      if (chip8->v[x] != chip8->v[y]) {
        chip8->pc += 2;
      }
      break;
    }
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Opcode desconhecido!", NULL);
    return false;
  }

  case 0xA000: {
    uint16_t nnn = chip8->opcode & 0x0FFF;
    chip8->I = nnn;
    break;
  }

  case 0xB000: {
    uint16_t nnn = chip8->opcode & 0x0FFF;
    chip8->pc = nnn + chip8->v[0];
    return true;
  }

  case 0xC000: {
    uint8_t random_byte = rand() % 256;

    uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->opcode & 0x00FF;

    chip8->v[x] = random_byte & nn;
    break;
  }

  case 0xD000: {
    uint8_t x = chip8->v[(chip8->opcode & 0x0F00) >> 8];
    uint8_t y = chip8->v[(chip8->opcode & 0x00F0) >> 4];
    uint8_t n = chip8->opcode & 0x000F;

    chip8->v[0xF] = 0;

    for (uint8_t row = 0; row < n; row++) {
      uint8_t sprite_byte = chip8->memory[chip8->I + row];

      for (uint8_t col = 0; col < 8; col++) {
        uint8_t mask = 0x80 >> col;

        if (sprite_byte & mask) {
          uint8_t px = (x + col) % 64;
          uint8_t py = (y + row) % 32;
          int index = PIXEL(px, py);

          if (chip8->framebuffer[index]) {
            chip8->v[0xF] = true;
          }

          chip8->framebuffer[index] ^= true;
        }
      }
    }
    break;
  }

  case 0xE000: {
    switch ((chip8->opcode & 0x00FF)) {

    case 0x9E: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;

      if (chip8->keypad[x]) {
        chip8->pc += 2;
      }
      break;
    }

    case 0xA1: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;

      if (!chip8->keypad[x]) {
        chip8->pc += 2;
      }
      break;
    }
    }
  }

  case 0xF000: {
    switch (chip8->opcode & 0x00FF) {
    case 0x0A: {
      uint8_t x = (chip8->opcode & 0x0F00) >> 8;

      for (uint8_t i = 0; i < 16; i++) {
        if (chip8->keypad[i]) {
          chip8->v[x] = i;
          chip8->pc += 2;
          return true;
        }
      }

      chip8->pc -= 2;
      break;
    } break;
    }
  }

  default:
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Opcode desconhecido!", NULL);
    return false;
    break;
  }

  chip8->pc += 2;

  return true;
}
