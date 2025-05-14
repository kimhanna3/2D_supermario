#pragma once

#include "map.h"

typedef struct {
    int x, y;         // current position
    int direction;    // +1 (right) or -1 (left)
    bool alive;       // allow future expansion (death, respawn)
} enemy_t;

#define MAX_ENEMIES 10

void enemy_init(enemy_t* e, int x, int y, int dir);
void enemy_update(enemy_t* e, map_t* map);
void enemy_draw(enemy_t* e, coord_t viewport);
