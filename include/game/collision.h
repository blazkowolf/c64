#ifndef COLLISION_H
#define COLLISION_H

#include "math.h"
#include <ultra64.h>

#define COLL_TYPE_FLOOR   1
#define COLL_TYPE_WALL    2
#define COLL_TYPE_CEILING 4 // Officially known as "TOP"

typedef struct CollisionTri {
    union {
        u8 type;
        // For example, footstep_sfx. If 0x80, fall death.
        // If 0xA2, lava death.
        u8 variable;
        u16 type_and_variable;
    };
    Vec3 vtx_pos[3]; // Vertices positions
} CollisionTri;

#endif
