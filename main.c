#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "map.h"
#include "mario.h"
#include "util.h"
#include "assets.h"
#include "enemy.h"

#define FRAME_RATE 30
#define MAX_FALL_SPEED 3
#define ENEMY_UPDATE_INTERVAL 10

enemy_t enemies[MAX_ENEMIES];
int num_enemies = 1; // for now, just one

// Returns true if Mario is standing on solid ground
bool mario_on_ground(mario_t* m, map_t* map) {
    return !map_is_walkable(map, m->x, m->y + 1);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mapfile>\n", argv[0]);
        return 1;
    }

    // Load map
    map_t map;
    if (!map_load(argv[1], &map)) {
    fprintf(stderr, "Failed to load map.\n");
    return 1;
    }
    map.start.x = 5;
    map.start.y = map.height - 2;

    // Init ncurses
    initscr();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    noecho();
    cbreak();
    curs_set(0);

    // Mario
    mario_t mario = { .x = 5, .y = 10 }; // Starting position
    mario_init(&mario, 5, map.height - 2);  // Near bottom

    // Viewport
    coord_t viewport = {0, 0};
    
    int last_direction = 0;  // -1 for left, 1 for right, 0 for no movement

    // Center viewport vertically on Mario
    viewport.y = mario.y - 10;
    if (viewport.y < 0) viewport.y = 0;
    if (viewport.y > (int)(map.height - 20)) viewport.y = map.height - 20;

    // Center horizontally
    viewport.x = mario.x - 10;
    if (viewport.x < 0) viewport.x = 0;
    if (viewport.x > (int)(map.width - 20)) viewport.x = map.width - 20;

    // Immediately draw the map and Mario
    clear();
    map_draw(&map, viewport);
    mario_draw(&mario, viewport);
    refresh();

    // Place enemy
    enemy_init(&enemies[0], 26, map.start.y, 1);

    bool running = true;
    while (running) {
        // Draw everything
        clear();
        map_draw(&map, viewport);     // Draw map with viewport
        mario_draw(&mario, viewport); // Draw Mario with viewport
        // Update and draw enemies
        for (int i = 0; i < num_enemies; i++) {
            enemy_update(&enemies[i], &map); // call n times per frame
            enemy_draw(&enemies[i], viewport);
        }
        refresh();

        int input = getch();
        if (input == 'q') {
            running = false;
        } else if (input == KEY_LEFT || input == 'a') {
            int new_x = mario.x - 1;
            if (map_is_walkable(&map, new_x, mario.y)) {
                mario.x = new_x;
                last_direction = -1;  // moving left
            }
        } else if (input == KEY_RIGHT || input == 'd') {
            int new_x = mario.x + 1;
            if (map_is_walkable(&map, new_x, mario.y)) {
                mario.x = new_x;
                last_direction = 1;  // moving right
            }
        } else if ((input == ' ' || input == KEY_UP) && mario_on_ground(&mario, &map)) {
            mario.jumping = true;
            mario.jump_frames = 8;
            mario.vy = -3;
            mario.jump_direction = last_direction;
        }

        // Update viewport to follow Mario horizontally and vertically
        viewport.x = mario.x - 10;
        if (viewport.x < 0) viewport.x = 0;
        if (viewport.x > (int)(map.width - 20)) viewport.x = map.width - 20;

        viewport.y = mario.y - 10;
        if (viewport.y < 0) viewport.y = 0;
        if (viewport.y > (int)(map.height - 20)) viewport.y = map.height - 20;

        // Gravity check
        if (!mario_apply_gravity(&mario, &map)) {
            clear();
            mvprintw(10, 10, "GAME OVER!");
            mvprintw(12, 10, "Press R to restart or Q to quit.");
            refresh();

            int choice;
            while ((choice = getch()) != 'q' && choice != 'r') {
                sleep_ms(100);
            }

            if (choice == 'r') {
                mario_init(&mario, map.start.x, map.start.y);
                viewport.x = 0;
                viewport.y = 0;
                continue;
            } else {
                running = false;
            }
        }

        // Clamp upward movement: check all intermediate steps (if vy < 0)
        while (mario.vy < 0) {
            if (map_is_walkable(&map, mario.x, mario.y - 1)) {
                mario.y--;
                mario.vy++;
            } else {
                mario.vy = 0;
                break;
            }
            if (mario.jump_direction != 0) {
                int new_x = mario.x + mario.jump_direction;
                if (map_is_walkable(&map, new_x, mario.y)) {
                    mario.x = new_x;
                }
            }
        }
        
        // Apply gravity acceleration
        if (!mario_on_ground(&mario, &map)) {
            mario.vy += 1;
            if (mario.vy > MAX_FALL_SPEED) {
                mario.vy = MAX_FALL_SPEED; // Terminal velocity
            }
        }

        // Check for Mario collision with enemy
        for (int i = 0; i < num_enemies; i++) {
            if (enemies[i].alive &&
                enemies[i].x == mario.x &&
                enemies[i].y == mario.y) {
                clear();
                mvprintw(10, 10, "You were attacked by an enemy!");
                mvprintw(12, 10, "Press R to restart or Q to quit.");
                refresh();

                int choice;
                while ((choice = getch()) != 'q' && choice != 'r') {
                    sleep_ms(100);
                }

                if (choice == 'r') {
                    mario_init(&mario, map.start.x, map.start.y);
                    viewport.x = 0;
                    viewport.y = 0;
                    continue;
                } else {
                    running = false;
                }
            }
        }

        // Falling: step downward and stop on collision
        while (mario.vy > 0) {
            if (map_is_walkable(&map, mario.x, mario.y + 1)) {
                mario.y++;
                mario.vy--;
            } else {
                // Collision with platform below
                mario.vy = 0;
                mario.jumping = false;
                break;
            }
        }
        char tile_under_mario = map_get_tile(&map, mario.x, mario.y);
        mvprintw(0, 0, "Tile: %c (%d,%d)", map_get_tile(&map, mario.x, mario.y), mario.x, mario.y);

        if (tile_under_mario == '*') {
            clear();
            mvprintw(10, 10, "LEVEL COMPLETE!");
            mvprintw(12, 10, "Press R to restart or Q to quit.");
            refresh();

            int choice;
            while ((choice = getch()) != 'q' && choice != 'r') {
                sleep_ms(100);
            }

            if (choice == 'r') {
                mario_init(&mario, map.start.x, map.start.y);
                viewport.x = 0;
                viewport.y = 0;
                continue;;
            } else {
                running = false;
            }
        }
        sleep_ms(1000 / FRAME_RATE);  // Control frame rate
    }

    // Apply gravity if not moving vertically
    if (mario.vy == 0 && map_is_walkable(&map, mario.x, mario.y + 1)) {
        mario.vy = 1;
        mario.jumping = true;
    }

    endwin();
    map_free(&map);
    return 0;
}
