/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Functions involving the player
*/

#include "../include/wolf3d.h"

player_t *create_player(void)
{
    player_t *player = malloc(sizeof(player_t));

    if (!player)
        return NULL;
    player->pos.x = 2.0f;
    player->pos.y = 2.0f;
    player->angle = 0.0f;
    player->speed = 3.0f;
    player->rot_speed = 2.0f;
    return player;
}

static int is_wall(map_t *map, float x, float y)
{
    if (x < 0 || x >= map->map_width || y < 0 || y >= map->map_height)
        return 1;
    if (map->tiles[(int)y][(int)x])
        return 1;
    return 0;
}

void move_player(player_t *player, map_t *map, float dt)
{
    sfVector2f next = {player->pos.x, player->pos.y};
    float move_step = player->speed * dt;

    if (sfKeyboard_isKeyPressed(sfKeyW)) {
        next.x += cos(player->angle) * move_step;
        next.y += sin(player->angle) * move_step;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        next.x -= cos(player->angle) * move_step;
        next.y -= sin(player->angle) * move_step;
    }
    if (!is_wall(map, next.x, player->pos.y))
        player->pos.x = next.x;
    if (!is_wall(map, player->pos.x, next.y))
        player->pos.y = next.y;
    if (sfKeyboard_isKeyPressed(sfKeyA))
        player->angle -= player->rot_speed * dt;
    if (sfKeyboard_isKeyPressed(sfKeyD))
        player->angle += player->rot_speed * dt;
}
