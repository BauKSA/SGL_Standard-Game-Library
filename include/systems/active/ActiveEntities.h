#ifndef _ACTIVEENTITIES_H_
#define _ACTIVEENTITIES_H_
#include <stdbool.h>

#include <types/Entity.h>

extern bool Entity_IsActive(Entity entity);
extern void Entity_Activate(Entity entity);
extern void Entity_Deactivate(Entity entity);

#endif // _ACTIVEENTITIES_H_