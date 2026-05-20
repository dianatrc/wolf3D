/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Functions for saving system
*/

#include "include/wolf3d.h"

int save_game(wolf_t *wolf, char *filepath)
{
    FILE *file = fopen(filepath, "w");

    if (!file)
        return 84;
    fprintf(file, "%f %f\n", wolf->player->pos.x, wolf->player->pos.y);
    fprintf(file, "%f %f\n", wolf->player->dir.x, wolf->player->dir.y);
    fprintf(file, "%f %f\n", wolf->player->plane.x, wolf->player->plane.y);
    fprintf(file, "%d\n", wolf->flash_on);
    fclose(file);
    sfSound_play(wolf->sounds->save);
    return 0;
}

int load_save(wolf_t *wolf, char *filepath)
{
    FILE *file = fopen(filepath, "r");

    if (!file)
        return 84;
    fscanf(file, "%f %f\n", &wolf->player->pos.x, &wolf->player->pos.y);
    fscanf(file, "%f %f\n", &wolf->player->dir.x, &wolf->player->dir.y);
    fscanf(file, "%f %f\n", &wolf->player->plane.x, &wolf->player->plane.y);
    fscanf(file, "%d\n", &wolf->flash_on);
    fclose(file);
    return 0;
}
