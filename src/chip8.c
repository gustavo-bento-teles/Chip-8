#include "include/chip8.h"

#include <stdbool.h>
#include <memory.h>

void chip8_init(Chip8* chip8) {
    memset(chip8->framebuffer, 0, sizeof(chip8->framebuffer));
    memset(chip8->memory, 0, sizeof(chip8->memory));
    memset(chip8->v, 0, sizeof(chip8->v));
    memset(chip8->stack, 0, sizeof(chip8->stack));

    chip8->sp = 0;
    chip8->pc = 0x200; // padrão CHIP-8
}

void chip8_fetch(Chip8* chip8) {
    uint8_t first_byte = chip8->memory[chip8->pc];
    uint8_t second_byte = chip8->memory[chip8->pc + 1];

    chip8->opcode = (first_byte << 8) | second_byte;
}

void chip8_execute(Chip8* chip8) {

    switch (chip8->opcode & 0xF000) {

        case 0x0000: {
            switch (chip8->opcode) {

                case 0x00E0:
                    memset(chip8->framebuffer, 0, sizeof(chip8->framebuffer));
                    break;

                case 0x00EE:
                    chip8->sp--;
                    chip8->pc = chip8->stack[chip8->sp];
                    break;
            }
            break;
        }

        case 0x1000: {
            uint16_t nnn = chip8->opcode & 0x0FFF;
            chip8->pc = nnn;
            return;
        }

        case 0x2000: {
            uint16_t nnn = chip8->opcode & 0x0FFF;

            chip8->stack[chip8->sp] = chip8->pc;
            chip8->sp++;

            chip8->pc = nnn;
            return;
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
            uint8_t x = (chip8->opcode & 0x0F00) >> 8;
            uint8_t y = (chip8->opcode & 0x00F0) >> 4;

            if (chip8->v[x] == chip8->v[y]) {
                chip8->pc += 2;
            }
            break;
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
            uint8_t x = (chip8->opcode & 0x0F00) >> 8;
            uint8_t y = (chip8->opcode & 0x00F0) >> 4;

            chip8->v[x] = chip8->v[y];
            break;
        }

        case 0x9000: {
            uint8_t x = (chip8->opcode & 0x0F00) >> 8;
            uint8_t y = (chip8->opcode & 0x00F0) >> 4;

            if (chip8->v[x] != chip8->v[y]) {
                chip8->pc += 2;
            }
            break;
        }

        case 0xA000: {
            uint16_t nnn = chip8->opcode & 0x0FFF;
            chip8->I = nnn;
            break;
        }

        case 0xB000: {
            uint16_t nnn = chip8->opcode & 0x0FFF;
            chip8->pc = nnn + chip8->v[0];
            return;
        }

        default:
            break;
    }
}