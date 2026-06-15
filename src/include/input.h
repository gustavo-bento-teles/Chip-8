#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

void update_keyboard(bool *keypad, const Uint8 *keyboard) {
  keypad[0x1] = keyboard[SDL_SCANCODE_1];
  keypad[0x2] = keyboard[SDL_SCANCODE_2];
  keypad[0x3] = keyboard[SDL_SCANCODE_3];
  keypad[0xC] = keyboard[SDL_SCANCODE_4];

  keypad[0x4] = keyboard[SDL_SCANCODE_Q];
  keypad[0x5] = keyboard[SDL_SCANCODE_W];
  keypad[0x6] = keyboard[SDL_SCANCODE_E];
  keypad[0xD] = keyboard[SDL_SCANCODE_R];

  keypad[0x7] = keyboard[SDL_SCANCODE_A];
  keypad[0x8] = keyboard[SDL_SCANCODE_S];
  keypad[0x9] = keyboard[SDL_SCANCODE_D];
  keypad[0xE] = keyboard[SDL_SCANCODE_F];

  keypad[0xA] = keyboard[SDL_SCANCODE_Z];
  keypad[0x0] = keyboard[SDL_SCANCODE_X];
  keypad[0xB] = keyboard[SDL_SCANCODE_C];
  keypad[0xF] = keyboard[SDL_SCANCODE_V];
}
