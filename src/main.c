#include <stdio.h>
#include <stdint.h>

#include "types/Entity.h"
#include "types/Memory.h"
#include "types/Vector.h"

#include "components/Active.h"
#include "components/Position.h"
#include "components/Speed.h"
#include "components/RigidBody.h"

#include "components/Mask.h"
#include <Components.h>

#include "systems/active/ActiveEntities.h"
#include "systems/physics/PhysicsSystem.h"

#define TEST_FORCE 40   // fuerza constante aplicada cada frame, en punto fijo

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

    for (uint32_t frame = 1; frame <= 75; frame++) {
        Vector2 force = { TEST_FORCE, 0 };
        RigidBody_ApplyForces(entity, force); // se re-aplica cada frame

        PhysicsSystem_Update();

        RigidBody* rb_ptr = &RigidBody_Pool[entity];
        printf("%5u | %8d | %10d | %10d\n",
            frame, TEST_FORCE, rb_ptr->velocity.x, Position_Pool[entity].real.x);
    }

    printf("\nDone: 75 frames\n\n");

    Memory_Diagnostics();

    return 0;
}