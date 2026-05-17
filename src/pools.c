#include <types/Entity.h>

#include <components/Active.h>
#include <components/RigidBody.h>
#include <components/Speed.h>
#include <components/Position.h>

Active Active_Pool[ACTIVE_POOL_SIZE] = { 0 };
RigidBody RigidBody_Pool[MAX_ENTITIES];
Speed Speed_Pool[MAX_ENTITIES] = { 0 };
Position Position_Pool[MAX_ENTITIES] = { 0 };