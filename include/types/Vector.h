#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <types/Memory.h>

typedef struct Vector2 {
	fxmem_uint x;
	fxmem_uint y;
} Vector2;

typedef struct Vector2m {
	fxmem_multiplicator x;
	fxmem_multiplicator y;
} Vector2m;

#endif // _VECTOR_H_