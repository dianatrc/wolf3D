/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Functions for the wolf3d structure
*/

#include "../include/wolf3d.h"

int init_wolf(wolf_t *wolf)
{
    wolf->style = sfClose | sfResize;
    wolf->window = create_my_window(1280, 720, wolf->style);
    wolf->map = create_map(MAP_WIDTH, MAP_HEIGHT);
    wolf->player = create_player();
    wolf->clock = sfClock_create();
    if (!wolf->window || !wolf->map || !wolf->player || !wolf->clock)
        return 84;
    return 0;
}

void free_wolf(wolf_t *wolf)
{
    if (wolf->window)
        sfRenderWindow_destroy(wolf->window);
    if (wolf->map)
        free_map(wolf->map);
    if (wolf->player)
        free(wolf->player);
    if (wolf->clock)
        sfClock_destroy(wolf->clock);
}
