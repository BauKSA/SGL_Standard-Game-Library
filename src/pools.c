#include <components/Active.h>
#include <components/RigidBody.h>
#include <components/Speed.h>
#include <components/Position.h>

#include <components/Mask.h>

Active Active_Pool[ACTIVE_POOL_SIZE] = { 0 };
RigidBody RigidBody_Pool[MAX_ENTITIES];
Speed Speed_Pool[MAX_ENTITIES] = { 0 };
Position Position_Pool[MAX_ENTITIES] = { 0 };

ComponentMask Entity_Mask[MAX_ENTITIES] = { 0 };