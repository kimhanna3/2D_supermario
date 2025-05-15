#pragma once
#include "map.h"

// Structure representing Mario's state
typedef struct {
    int x, y;             // Current position on the map (grid coordinates)
    int vy;               // Vertical velocity (positive = falling, negative = jumping up)
    bool jumping;         // True if Mario is currently in a jump
    int jump_frames;      // Remaining frames of jump duration
    int jump_direction;   // Direction of jump: -1 = left, 1 = right, 0 = straight up
} mario_t;

void mario_init(mario_t* m, int x, int y);
void mario_draw(mario_t* m, coord_t viewport);
bool mario_apply_gravity(mario_t* m, map_t* map);
