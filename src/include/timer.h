#pragma once
#include <SDL2/SDL.h>

const double TIMER_INTERVAL = 1.0 / 60.0;

double timer_acumulator = 0.0;

Uint32 last_ticks;
