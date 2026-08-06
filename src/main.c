#include <types/Entity.h>
#include <types/Memory.h>

#include <components/Speed.h>
#include <components/Position.h>
#include <components/Active.h>
#include <components/RigidBody.h>

#include <systems/entity/CreateEntity.h>
#include <systems/active/ActiveEntities.h>
#include <systems/physics/PhysicsSystem.h>

#include <types/Vector.h>

#include <stdio.h>
#include <stdint.h>

static void Memory_Diagnostics() {
	size_t total_ram = sizeof(Position_Pool) + sizeof(Speed_Pool) + sizeof(Active_Pool);

	printf("--- ECS RAM USAGE ---\n");
	printf("Active Pool:    %zu bytes\n", sizeof(Active_Pool));
	printf("Position Pool: %zu bytes\n", sizeof(Position_Pool));
	printf("Speed Pool:    %zu bytes\n", sizeof(Speed_Pool));
	printf("Total RAM: %.8f KB\n", (float)total_ram / 1024.0f);
	printf("---------------------\n");
}

int main(int argc, char* argv[]) {
	Entity entity = Entity_Create();
	Speed_Pool[entity] = 60;
	Position pos = { {0,0}, {0,0} };
	Position_Pool[entity] = pos;

	RigidBody rb = { 0 };
	rb.mass = 1;
	rb.inverse_mass = 1 << FXD_SHIFT; // inverse_mass = 1.0 en punto fijo (1/1)
	RigidBody_Pool[entity] = rb;

	Entity_Activate(entity);

	printf("frame | forces.x | velocity.x | pos.real.x\n");
	printf("------|----------|------------|-----------\n");

	uint8_t f_count = 0;
	uint8_t counted = 0;

	for (uint32_t frame = 1; frame <= 75; frame++) {
		Vector2 force = { 200, 0 };
		RigidBody_ApplyForces(entity, force); // se re-aplica cada frame

		PhysicsSystem_Update();

		RigidBody* rb_ptr = &RigidBody_Pool[entity];
		printf("%5u | %8d | %10d | %10d\n",
			frame, 40, rb_ptr->velocity.x, Position_Pool[entity].real.x);

		if (Position_Pool[entity].real.x >= 1 && !counted) {
			f_count = frame;
			counted = 1;
		}

	}

	printf("\nDone: 75 frames\n\n");
	printf("\nFrames to x = 1: %u frames\n\n", f_count);

	Memory_Diagnostics();

    return 0;
}