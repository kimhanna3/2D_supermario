#include "map.h"
#include "assets.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

bool map_load(const char* filename, map_t* map) {
    FILE* f = fopen(filename, "r");
    if (!f) return false;

    map->width = 0;
    map->height = 0;
    map->data = NULL;

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        size_t len = strlen(line);
        if (line[len-1] == '\n') line[len-1] = '\0';
        size_t line_len = strlen(line);
        if (line_len > map->width) map->width = line_len;

        map->data = realloc(map->data, sizeof(char*) * (map->height + 1));
        // Allocate a full-width buffer
        map->data[map->height] = malloc(map->width + 1);
        memset(map->data[map->height], ' ', map->width);  // fill with spaces
        memcpy(map->data[map->height], line, line_len);   // copy only actual line data

        map->height++;
    }
    fclose(f);
    return true;
}

void map_free(map_t* map) {
    for (size_t i = 0; i < map->height; i++) {
        free(map->data[i]);
    }
    free(map->data);
}

void map_draw(map_t* map, coord_t viewport) {
    for (size_t y = 0; y < map->height; y++){
        // printf("%zu", map->width);
        for (size_t x = 0; x < map->width+1; x++){
            int screen_x = (x - viewport.x) * 2;
            int screen_y = y - viewport.y;

            if (screen_x >= 0 && screen_y >= 0 && screen_y < LINES && screen_x < COLS) {
                mvaddch(screen_y, screen_x, map->data[y][x]);
            }
        }
    }
}

bool map_is_walkable(map_t* map, int x, int y) {
    int width = (int) map->width;
    int height = (int) map->height;

    if (x < 0 || y < 0 || y >= height || x >= width) {
        return false;
    }

    char tile = map->data[y][x];
    return tile == TILE_EMPTY || tile == TILE_COIN;
}

char map_get_tile(map_t* map, int x, int y) {
    if (x < 0 || y < 0 || y >= (int)map->height || x == ((int)map->width)) {
        return TILE_EMPTY;
    }
    if ((int)strlen(map->data[y]) <= x) {
    return TILE_EMPTY;
}
return map->data[y][x];
}
