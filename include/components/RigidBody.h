#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_
#include <types/Vector.h>
#include <types/Memory.h>

typedef struct RigidBody {
	fxmem_uint mass;
	fxmem_uint inverse_mass;

	Vector2 velocity;
	Vector2 forces;
} RigidBody;

extern RigidBody RigidBody_Pool[MAX_ENTITIES];

#endif // !_RIGIDBODY_H_
