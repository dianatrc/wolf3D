/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Map structure management
*/

#include "../include/wolf3d.h"

static void free_tiles(int **tiles, int rows)
{
    for (int i = 0; i < rows; i++)
        free(tiles[i]);
    free(tiles);
}

static int get_tile_value(int width, int height, int x, int y)
{
    if (y == 0 || x == 0 || y == height - 1 || x == width - 1)
        return 1;
    return 0;
}

static int **init_map_tiles(int width, int height)
{
    int **tiles = malloc(height * sizeof(int *));

    if (!tiles)
        return NULL;
    for (int i = 0; i < height; i++) {
        tiles[i] = malloc(width * sizeof(int));
        if (!tiles[i]) {
            free_tiles(tiles, i);
            return NULL;
        }
        for (int j = 0; j < width; j++)
            tiles[i][j] = get_tile_value(width, height, j, i);
    }
    return tiles;
}

map_t *create_map(int width, int height)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return NULL;
    map->map_width = width;
    map->map_height = height;
    map->tiles = init_map_tiles(width, height);
    if (!map->tiles) {
        free(map);
        return NULL;
    }
    return map;
}

void free_map(map_t *map)
{
    if (!map)
        return;
    if (map->tiles)
        free_tiles(map->tiles, map->map_height);
    free(map);
}
