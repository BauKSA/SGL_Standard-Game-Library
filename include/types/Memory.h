#ifndef _MEMORY_H_
#define _MEMORY_H_
#include <stdint.h>

#ifdef LOWEST_MEMORY_SYS
/*
   Nivel 1: Lowest (8-bit)
   Game Boy, NES, Master System, Arduino
*/
typedef uint8_t fxmem_uint;
typedef int8_t  fxmem_int;
typedef int16_t fxmem_multiplicator;

#define BITS_PER_UNIT 8

#elif defined(LIMITED_MEMORY_SYS)
/*
   Nivel 2: Medium (16-bit)
   SNES, Sega Genesis, GBA
*/
typedef uint16_t fxmem_uint;
typedef int16_t  fxmem_int;
typedef int32_t fxmem_multiplicator;

#define BITS_PER_UNIT 16

#else
/*
   Nivel 3: Large/Standard (32-bit)
   PC, Nintendo DS, N64, PSX
*/
typedef uint32_t fxmem_uint;
typedef int32_t  fxmem_int;
typedef int64_t fxmem_multiplicator;

#define BITS_PER_UNIT 32

#endif // !LOWEST_MEMORY_SYS

#ifndef FPS
#define FPS 30
#endif // !FPS


#define FXD_SHIFT BITS_PER_UNIT
#define FXD_DT ((1 << FXD_SHIFT) / FPS)

#endif // !_MEMORY_H_