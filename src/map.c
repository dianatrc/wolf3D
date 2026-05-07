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

static int **alocate_tiles(int width, int height)
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
    }
    return tiles;
}

static map_t *init_map_struct(FILE *file)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return NULL;
    if (fscanf(file, "%d %d", &map->map_width, &map->map_height) != 2) {
        free(map);
        return NULL;
    }
    map->tiles = alocate_tiles(map->map_width, map->map_height);
    if (!map->tiles) {
        free(map);
        return NULL;
    }
    return map;
}

map_t *load_map(char *filename)
{
    FILE *file = fopen(filename, "r");
    map_t *map;

    if (!file)
        return NULL;
    map = init_map_struct(file);
    if (!map) {
        fclose(file);
        return NULL;
    }
    for (int i = 0; i < map->map_height; i++)
        for (int j = 0; j < map->map_width; j++)
            fscanf(file, "%d", &map->tiles[i][j]);
    fclose(file);
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
