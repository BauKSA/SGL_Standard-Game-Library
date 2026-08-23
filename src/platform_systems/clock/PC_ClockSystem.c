#ifdef PLATFORM_PC
#include <systems/clock/ClockSystem.h>
#include <types/Memory.h>

#include <time.h>
#include <stdio.h>

#define TICKS_PER_FRAME (CLOCKS_PER_SEC / FPS)

typedef struct {
    clock_t last_frame_clock;
    clock_t accumulator;
} ClockSystem;

static ClockSystem pc_clock;

void ClockSystem_Init(void) {
    pc_clock.last_frame_clock = clock();
    pc_clock.accumulator = 0;
}

void ClockSystem_Update(void) {
    clock_t now = clock();
    clock_t elapsed = now - pc_clock.last_frame_clock;

    clock_t remaining = TICKS_PER_FRAME - elapsed - pc_clock.accumulator;

    if (remaining > 0) {
        // busy-wait: clock() no tiene "sleep", así que esperamos activamente
        clock_t wait_until = now + remaining;
        while (clock() < wait_until) {
            // busy loop (consume CPU, pero es 100% portable en C estándar)
        }
        pc_clock.accumulator = 0;
    }
    else {
        // el frame se pasó de tiempo: acumulamos la "deuda"
        // para no ir arrastrando drift frame tras frame
        pc_clock.accumulator = -remaining;
    }

    pc_clock.last_frame_clock = clock();
}

#endif