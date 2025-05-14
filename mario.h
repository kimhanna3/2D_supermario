#pragma once
#include "map.h"

typedef struct {
    int x, y;
    int vy;           // vertical velocity
    bool jumping;     // is currently jumping
    int jump_frames;  // how many frames of jump remain
    int jump_direction; // -1 for left, 1 for right, 0 for straight up
} mario_t;

void mario_init(mario_t* m, int x, int y);
void mario_draw(mario_t* m, coord_t viewport);
bool mario_apply_gravity(mario_t* m, map_t* map);
