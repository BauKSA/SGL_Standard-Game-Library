#ifndef _PHYSICSSYSTEM_H_
#define _PHYSICSSYSTEM_H_

#include<types/Entity.h>
#include<types/Vector.h>

void PhysicsSystem_Update();
void RigidBody_ApplyForces(Entity entity, Vector2 forces);
void RigidBody_ClampSpeed(Entity entity);

#endif // !_PHYSICSSYSTEM_H_