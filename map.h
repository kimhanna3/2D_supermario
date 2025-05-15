#pragma once

#include <stddef.h>
#include <stdbool.h>

// Represents a coordinate (x, y) on the map
typedef struct {
    int x;
    int y;
} coord_t;

// Represents the entire map structure
typedef struct {
    char** data;   // 2D array of characters
    size_t width;  // Width of the map in characters
    size_t height; // Height of the map in lines
    coord_t start; // Starting coordinate for the player (e.g., Mario)
} map_t;

bool map_load(const char* filename, map_t* map);
void map_free(map_t* map);
void map_draw(map_t* map, coord_t viewport);
bool map_is_walkable(map_t* map, int x, int y);
char map_get_tile(map_t* map, int x, int y);
