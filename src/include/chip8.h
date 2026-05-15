#pragma once

#include <stdint.h>
#include <stdbool.h>

#define WIDTH_CHIP8 64
#define HEIGHT_CHIP8 32

typedef struct {
    uint8_t memory[4096];

    uint8_t v[16];

    uint16_t I;
    uint16_t pc;

    uint16_t stack[16];
    uint8_t sp;

    uint8_t delay_timer;
    uint8_t sound_timer;

    bool framebuffer[WIDTH_CHIP8 * HEIGHT_CHIP8];

    uint16_t opcode;
} Chip8;


void chip8_init(Chip8* chip8);

void chip8_fetch(Chip8* chip8);

void chip8_execute(Chip8* chip8);