#include <stdbool.h>
#include <components/Active.h>
#include <systems/active/ActiveEntities.h>
#include <types/Entity.h>

void Entity_Activate(Entity entity) {
    Active_Pool[entity / BITS_PER_UNIT] |= (1U << (entity % BITS_PER_UNIT));
}

// Función para desactivar una entidad
void Entity_Deactivate(Entity entity) {
    Active_Pool[entity / BITS_PER_UNIT] &= ~(1U << (entity % BITS_PER_UNIT));
}

bool Entity_IsActive(Entity entity) {
	return (Active_Pool[entity / BITS_PER_UNIT] & (1U << (entity % BITS_PER_UNIT))) != 0;
}