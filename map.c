#include "map.h"
#include "assets.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// Loads the map from a text file into the map_t structure
bool map_load(const char* filename, map_t* map) {
    FILE* f = fopen(filename, "r");
    if (!f) return false;

    map->width = 0;
    map->height = 0;
    map->data = NULL; // Initialize empty map data


    char line[1024]; // Buffer to read each line
    while (fgets(line, sizeof(line), f)) {
        size_t len = strlen(line);
        if (line[len-1] == '\n') line[len-1] = '\0'; // Remove newline
        size_t line_len = strlen(line);
        if (line_len > map->width) map->width = line_len; // Track widest line
        
        // Reallocate to store another row
        map->data = realloc(map->data, sizeof(char*) * (map->height + 1));
        
        // Allocate and initialize full-width row with spaces
        map->data[map->height] = malloc(map->width + 1);
        memset(map->data[map->height], ' ', map->width);  // fill with spaces
        memcpy(map->data[map->height], line, line_len);   // copy only actual line data

        map->height++; // Increase row count
    }
    fclose(f);
    return true;
}

// Frees the memory allocated for the map
void map_free(map_t* map) {
    for (size_t i = 0; i < map->height; i++) {
        free(map->data[i]);
    }
    free(map->data); // Free the row pointer array
}

// Draws the map to the screen using the viewport as the top-left offset
void map_draw(map_t* map, coord_t viewport) {
    for (size_t y = 0; y < map->height; y++){
        for (size_t x = 0; x < map->width; x++){
            int screen_x = (x - viewport.x) * 2; // Horizontal scale factor for better visibility
            int screen_y = y - viewport.y;
            // Only draw if within visible screen area
            if (screen_x >= 0 && screen_y >= 0 && screen_y < LINES && screen_x < COLS) {
                mvaddch(screen_y, screen_x, map->data[y][x]); // Draw character at computed position
            }
        }
    }
}

// Determines if a specific tile is walkable (i.e., not solid)
bool map_is_walkable(map_t* map, int x, int y) {
    int width = (int) map->width;
    int height = (int) map->height;

    if (x < 0 || y < 0 || y >= height || x >= width) {
        return false;
    }

    char tile = map->data[y][x];
    return tile == TILE_EMPTY; //  Only empty tiles are walkable

}

// Safely retrieves the tile character at a given position
char map_get_tile(map_t* map, int x, int y) {
    // Return TILE_EMPTY if out of bounds
    if (x < 0 || y < 0 || y >= (int)map->height || x == ((int)map->width)) {
        return TILE_EMPTY;
    }
    // Also check line length to avoid accessing uninitialized memory
    if ((int)strlen(map->data[y]) <= x) {
    return TILE_EMPTY;
}
return map->data[y][x];  // Return character at given coordinates
}
