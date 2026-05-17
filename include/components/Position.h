#ifndef _POSITION_H_
#define _POSITION_H_
#include <types/Vector.h>

typedef struct Position {
	Vector2 real;
	Vector2m fixed;
} Position;

extern Position Position_Pool[MAX_ENTITIES];

#endif // _POSITION_H_