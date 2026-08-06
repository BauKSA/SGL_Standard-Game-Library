#include<systems/physics/PhysicsSystem.h>
#include<systems/active/ActiveEntities.h>

#include<components/Position.h>
#include<components/RigidBody.h>
#include<components/Speed.h>

#include<types/Memory.h>
#include<types/Entity.h>
#include<types/Vector.h>

void PhysicsSystem_Update() {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		Entity entity = i;

		if (!Entity_IsActive(i)) continue;

		RigidBody* rigidBody = &RigidBody_Pool[i];
		Position* position = &Position_Pool[i];

		fxmem_int acceleration_x
			= (fxmem_multiplicator)(rigidBody->forces.x * rigidBody->inverse_mass) >> FXD_SHIFT;
		fxmem_int acceleration_y
			= (fxmem_multiplicator)(rigidBody->forces.y * rigidBody->inverse_mass) >> FXD_SHIFT;

		rigidBody->velocity.x +=
			(fxmem_int)((fxmem_multiplicator)acceleration_x * FXD_DT);
		rigidBody->velocity.y +=
			(fxmem_int)((fxmem_multiplicator)acceleration_y * FXD_DT);

		RigidBody_ClampSpeed(entity);

		position->fixed.x += ((fxmem_multiplicator)rigidBody->velocity.x * FXD_DT) >> FXD_SHIFT;
		position->fixed.y += ((fxmem_multiplicator)rigidBody->velocity.y * FXD_DT) >> FXD_SHIFT;

		position->real.x = position->fixed.x >> FXD_SHIFT;
		position->real.y = position->fixed.y >> FXD_SHIFT;

		rigidBody->forces.x = 0;
		rigidBody->forces.y = 0;
	}
}

void RigidBody_ApplyForces(Entity entity, Vector2 forces) {
	if (!Entity_IsActive(entity)) return;

	RigidBody* rigidBody = &RigidBody_Pool[entity];

	rigidBody->forces.x += forces.x;
	rigidBody->forces.y += forces.y;
}

void RigidBody_ClampSpeed(Entity entity) {
	RigidBody* rigidBody = &RigidBody_Pool[entity];
	Speed* speed = &Speed_Pool[entity];

	if (*speed == 0) return;

	fxmem_int speed_fixed = (fxmem_int)(*speed) << FXD_SHIFT; // 128 → 32768 (Q8.8)

	if (rigidBody->velocity.x > speed_fixed)  rigidBody->velocity.x = speed_fixed;
	if (rigidBody->velocity.x < -speed_fixed) rigidBody->velocity.x = -speed_fixed;
}