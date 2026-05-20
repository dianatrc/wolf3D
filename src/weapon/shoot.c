/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Shooting wall functions
*/

#include "include/wolf3d.h"

void shoot_wall(wolf_t *wolf)
{
    float target_x = 0.0f;
    float target_y = 0.0f;

    for (float dist = 0.1f; dist < 30.0f; dist += 0.1f) {
        target_x = wolf->player->pos.x + wolf->player->dir.x * dist;
        target_y = wolf->player->pos.y + wolf->player->dir.y * dist;
        if (target_x < 0 || target_x >= wolf->map->map_width ||
            target_y < 0 || target_y >= wolf->map->map_height)
            return;
        if (wolf->map->tiles[(int)target_y][(int)target_x] == 1)
            return;
        if (wolf->map->tiles[(int)target_y][(int)target_x] == 2) {
            wolf->map->tiles[(int)target_y][(int)target_x] = 0;
            return;
        }
    }
}
