#pragma once

#include <stdbool.h>
#include <stdint.h>

bool load_rom(const char *file_path, uint8_t *memory,
              uint16_t init_memory_address);
