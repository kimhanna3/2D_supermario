#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} coord_t;

typedef struct {
    char** data; // 2D array of characters
    size_t width;
    size_t height;
    coord_t start;
} map_t;

typedef enum {
    CELL_EMPTY,
    CELL_BRICK,
    CELL_GROUND,
    CELL_PIPE,
    CELL_COIN,
    CELL_GOAL
} cell_t;

bool map_load(const char* filename, map_t* map);
void map_free(map_t* map);
void map_draw(map_t* map, coord_t viewport);
bool map_is_walkable(map_t* map, int x, int y);
char map_get_tile(map_t* map, int x, int y);
