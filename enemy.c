#include "enemy.h"
#include "assets.h"
#include "ncurses.h"
#include "map.h"

void enemy_init(enemy_t* e, int x, int y, int dir) {
    e->x = x;
    e->y = y;
    e->direction = dir;
    e->alive = true;
}

void enemy_update(enemy_t* e, map_t* map) {
    if (!e->alive) return;

    int next_x = e->x + e->direction;

    // Check bounds + walkable tile ahead
    // if (!map_is_walkable(map, next_x, e->y) || !map_is_walkable(map, next_x, e->y + 1)) {
    //     e->direction *= -1; // turn around
    // } else {
        e->x += e->direction;
    // }
}

void enemy_draw(enemy_t* e, coord_t viewport) {
    if (!e->alive) return;

    int screen_x = (e->x - viewport.x) * 2;
    int screen_y = e->y - viewport.y;

    if (screen_x >= 0 && screen_y >= 0 && screen_y < LINES && screen_x < COLS) {
        mvaddch(screen_y, screen_x, 'E');  // enemy char
    }
}
