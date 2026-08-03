#ifndef _ACTIVE_H_
#define _ACTIVE_H_
#include <types/Entity.h>
#include <types/Memory.h>

#ifndef MAX_ENTITIES
#define ACTIVE_POOL_SIZE 8

#else
#if MAX_ENTITIES >= 8 && MAX_ENTITIES >= BITS_PER_UNIT
#define ACTIVE_POOL_SIZE (MAX_ENTITIES / BITS_PER_UNIT)
#else
#define ACTIVE_POOL_SIZE 8

#endif // MAX_ENTITIES > 8 && MAX_ENTITIES >= BITS_PER_UNIT

#endif // !MAX_ENTITIES+


typedef fxmem_uint Active;

extern Active Active_Pool[ACTIVE_POOL_SIZE];

#endif // _ACTIVE_H_