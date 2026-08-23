#include <stdio.h>
#include <stdint.h>

#include <types/Entity.h>
#include <types/Memory.h>
#include <types/Vector.h>

#include <components/Active.h>
#include <components/Position.h>
#include <components/Speed.h>
#include <components/RigidBody.h>

#include <components/Mask.h>
#include <Components.h>

#include <systems/active/ActiveEntities.h>
#include <systems/physics/PhysicsSystem.h>
#include <systems/clock/ClockSystem.h>

#include <core/window/Window.h>

static void Memory_Diagnostics() {
	size_t total_ram = sizeof(Position_Pool) + sizeof(Speed_Pool) + sizeof(Active_Pool);

	printf("--- ECS RAM USAGE ---\n");
	printf("Active Pool:    %zu bytes\n", sizeof(Active_Pool));
	printf("Position Pool: %zu bytes\n", sizeof(Position_Pool));
	printf("Speed Pool:    %zu bytes\n", sizeof(Speed_Pool));
	printf("RigidBody Pool: %zu bytes\n", sizeof(RigidBody_Pool));

	printf("Total RAM: %.8f KB\n", (float)total_ram / 1024.0f);
	printf("---------------------\n");
}

int main(int argc, char* argv[]) {
	Entity entity = Entity_Create();

	Position pos = { {0,0}, {0,0} };
	Position_Pool[entity] = pos;

	RigidBody rb = { 0 };
	rb.mass = 1;
	rb.inverse_mass = 1 << FXD_SHIFT; // inverse_mass = 1.0 en punto fijo (1/1)
	RigidBody_Pool[entity] = rb;
	MASK_SET(entity, COMPONENT_RIGIDBODY);

	Speed_Pool[entity] = 128; // velocidad máxima permitida

	Entity_Activate(entity);

	printf("frame | forces.x | velocity.x | pos.real.x\n");
	printf("------|----------|------------|-----------\n");

	fxmem_int prev_velocity = 0;
	fxmem_int expected_delta = 0;
	int clamp_notified = 0;

	Window_Config config = {
		.title = "Test",
		.width = 800,
		.height = 600,
		.mode = WINDOWED
	};

	fxmem_int error = !Window_Init(&config);
	if (error) return;

	ClockSystem_Init();

	for (uint32_t frame = 1; frame <= 600; frame++) {
		Vector2 force = { 40, 0 };
		RigidBody_ApplyForces(entity, force); // se re-aplica cada frame

		PhysicsSystem_Update();

		RigidBody* rb_ptr = &RigidBody_Pool[entity];
		fxmem_int current_velocity = rb_ptr->velocity.x;
		fxmem_int delta = current_velocity - prev_velocity;

		if (frame == 1) {
			expected_delta = delta;
		}
		else if (!clamp_notified && delta < expected_delta) {
			printf(">> [CLAMP] activado en frame %u: velocity.x=%d (delta=%d, esperado=%d)\n",
				frame, current_velocity, delta, expected_delta);
			clamp_notified = 1;
		}

		printf("%5u | %8d | %10d | %10d\n",
			frame, 40, current_velocity, Position_Pool[entity].real.x);

		prev_velocity = current_velocity;

		ClockSystem_Update();
	}

	Memory_Diagnostics();

	return 0;
}