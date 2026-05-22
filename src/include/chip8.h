#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#define WIDTH_CHIP8 64
#define HEIGHT_CHIP8 32

#define PIXEL(x, y) ((y) * WIDTH_CHIP8 + (x))

#define STACK_SIZE 16

#define MEMORY_SIZE 4096
#define MEMORY_INIT_POINT 0x200

typedef struct {
  uint8_t memory[MEMORY_SIZE];

  uint8_t v[16];

  uint16_t I;
  uint16_t pc;

  uint16_t stack[STACK_SIZE];
  uint8_t sp;

  uint8_t delay_timer;
  uint8_t sound_timer;

  bool framebuffer[WIDTH_CHIP8 * HEIGHT_CHIP8];

  uint16_t opcode;
} Chip8;

void chip8_init(Chip8 *chip8);

void chip8_fetch(Chip8 *chip8);

bool chip8_execute(Chip8 *chip8);
