#include <systems/movement/MovementSystem.h>
#include <systems/active/ActiveEntities.h>

#include <components/Position.h>
#include <components/Speed.h>

#include <types/Entity.h>
#include <types/Memory.h>

void MovementSystem_Update() {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		Entity entity = i;
		if (!Entity_IsActive(i)) continue;

		Position *pos = &Position_Pool[i];
		Speed speed = Speed_Pool[i];

		pos->fixed.x += speed;
		pos->real.x = pos->fixed.x >> FXD_SHIFT;
	}
}