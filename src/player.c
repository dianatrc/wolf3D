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
    player->pos = (sfVector2f){1.5f, 1.5f};
    player->dir = (sfVector2f){1.0f, 0.0f};
    player->plane = (sfVector2f){0.0f, 0.66f};
    player->speed = 3.0f;
    player->rot_speed = 2.0f;
    return player;
}

int is_wall(map_t *map, float x, float y)
{
    if (x < 0 || x >= map->map_width || y < 0 || y >= map->map_height)
        return 1;
    if (map->tiles[(int)y][(int)x])
        return 1;
    return 0;
}

static void rotate_player(player_t *player, float rot_speed)
{
    float old_dir_x = player->dir.x;
    float old_plane_x = player->plane.x;

    player->dir.x = player->dir.x * cos(rot_speed) -
        player->dir.y * sin(rot_speed);
    player->dir.y = old_dir_x * sin(rot_speed) +
        player->dir.y * cos(rot_speed);
    player->plane.x = player->plane.x * cos(rot_speed) -
        player->plane.y * sin(rot_speed);
    player->plane.y = old_plane_x * sin(rot_speed) +
        player->plane.y * cos(rot_speed);
}

static void handle_movement(player_t *player, sfVector2f *next, float move_step)
{
    if (sfKeyboard_isKeyPressed(sfKeyW)) {
        next->x += player->dir.x * move_step;
        next->y += player->dir.y * move_step;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        next->x -= player->dir.x * move_step;
        next->y -= player->dir.y * move_step;
    }
}

void move_player(player_t *player, map_t *map, float dt)
{
    sfVector2f next = {player->pos.x, player->pos.y};
    float current_speed = player->speed;
    float move_step = 0.0f;
    float rot_step = player->rot_speed * dt;

    if (sfKeyboard_isKeyPressed(sfKeyLShift))
        current_speed *= 2.0f;
    move_step = current_speed * dt;
    handle_movement(player, &next, move_step);
    if (!is_wall(map, next.x, player->pos.y))
        player->pos.x = next.x;
    if (!is_wall(map, player->pos.x, next.y))
        player->pos.y = next.y;
    if (sfKeyboard_isKeyPressed(sfKeyA))
        rotate_player(player, -rot_step);
    if (sfKeyboard_isKeyPressed(sfKeyD))
        rotate_player(player, rot_step);
}
