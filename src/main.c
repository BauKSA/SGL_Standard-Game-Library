#include <types/Entity.h>
#include <types/Memory.h>

#include <components/Speed.h>
#include <components/Position.h>
#include <components/Active.h>

#include <systems/entity/CreateEntity.h>
#include <systems/active/ActiveEntities.h>
#include <systems/movement/MovementSystem.h>

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
	Speed_Pool[entity] = 156;
	Position pos = { {0,0}, {0,0} };
	Position_Pool[entity] = pos;

	Entity_Activate(entity);

	uint8_t counter = 0;

	while (1) {
		MovementSystem_Update();

		counter++;

		if (Position_Pool[entity].real.x > 1) break;
	}

	printf("\nNeeded %d frames to move 1px\n\n\n", counter);

	Memory_Diagnostics();

    return 0;
}