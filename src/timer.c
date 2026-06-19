#include "include/timer.h"

const double TIMER_INTERVAL = 1.0 / 60.0;
const double CPU_INTERVAL = 1.0 / 500.0;

double timer_accumulator = 0.0;
double cpu_accumulator = 0.0;

Uint64 last_ticks = 0;
Uint64 cpu_last_ticks = 0;
