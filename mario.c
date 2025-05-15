#include "mario.h"
#include "assets.h"
#include "map.h"
#include <ncurses.h>

// Initializes Mario's position and vertical velocity
void mario_init(mario_t* m, int x, int y) {
    m->x = x;  // Set Mario's horizontal position
    m->y = y;  // Set Mario's vertical position
    m->vy = 0; // Reset vertical velocity
}

// Draws Mario on the screen using his position relative to the viewport
void mario_draw(mario_t* m, coord_t viewport) {
    int screen_x = (m->x - viewport.x) * 2;
    int screen_y = m->y - viewport.y;
    mvaddch(screen_y, screen_x, MARIO_CHAR);
}

// Applies gravity to Mario. Returns false if he falls out of bounds (game over)
bool mario_apply_gravity(mario_t* m, map_t* map) {
    int below_y = m->y + 1;

    if (below_y >= (int)map->height) {
        return false;  // Mario has fallen out of bounds
    }

    if (map_is_walkable(map, m->x, below_y)) {
        m->y += 1;  // Apply gravity by moving Mario down
    }

    return true;  // Mario is still within bounds
}

// Attempts to initiate a jump. Only works if Mario is on solid ground
void mario_jump(mario_t* m, map_t* map) {
    // Allow jump only if standing on something
    if (!map_is_walkable(map, m->x, m->y + 1)) {
        m->vy = -3; // small upward velocity to start the jump
    }
}
