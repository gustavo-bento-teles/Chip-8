#pragma once
#include <SDL2/SDL.h>

extern const double TIMER_INTERVAL;
extern const double CPU_INTERVAL;

extern double timer_accumulator;
extern double cpu_accumulator;

extern Uint64 last_ticks;
extern Uint64 cpu_last_ticks;
