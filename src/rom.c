#include "include/rom.h"
#include "chip8.h"
#include <stdio.h>

bool load_rom(const char *file_path, uint8_t *memory,
              uint16_t init_memory_address) {

  FILE *rom = fopen(file_path, "rb");

  if (!rom) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Falha ao abrir arquivo!", NULL);

    return false;
  }

  fseek(rom, 0, SEEK_END);

  long rom_size = ftell(rom);

  if (rom_size < 0) {

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Falha ao obter tamanho da ROM!", NULL);

    fclose(rom);
    return false;
  }

  rewind(rom);

  if (rom_size > (MEMORY_SIZE - init_memory_address)) {

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "ROM grande demais para memória do CHIP-8!", NULL);

    fclose(rom);
    return false;
  }

  size_t bytes_read = fread(&memory[init_memory_address], 1, rom_size, rom);

  if (bytes_read != (size_t)rom_size) {

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erro",
                             "Falha ao ler ROM completamente!", NULL);

    fclose(rom);
    return false;
  }

  fclose(rom);

  return true;
}
