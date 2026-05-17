#include <systems/entity/CreateEntity.h>
#include <types/Entity.h>

Entity Entity_Create() {
	return entity_count++;
}