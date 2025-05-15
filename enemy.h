#pragma once

#include "map.h" // Required for coord_t and map_t used in function signatures

// Structure representing an enemy in the game
typedef struct {
    int x, y;         // current position (x = horizontal, y = vertical)
    int direction;    // +1 (right) or -1 (left)
    bool alive;       // Flag to indicate if the enemy is active (used for future logic like death)
} enemy_t;

#define MAX_ENEMIES 10

void enemy_init(enemy_t* e, int x, int y, int dir);
void enemy_update(enemy_t* e, map_t* map);
void enemy_draw(enemy_t* e, coord_t viewport);
