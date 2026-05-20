/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Raycast logic using the DDA algorithm
*/

#include "include/wolf3d.h"
#include "include/raycast.h"

static float get_delta_dist(float dir)
{
    float delta = 0;

    if (dir == 0)
        return 100000.0f;
    delta = 1 / dir;
    if (delta < 0)
        delta *= -1;
    return delta;
}

void init_ray(raycast_t *ray, player_t *player, int x)
{
    float camera_x = (2 * x / (float) 1280) - 1;

    ray->pos = player->pos;
    ray->dir.x = player->dir.x + player->plane.x * camera_x;
    ray->dir.y = player->dir.y + player->plane.y * camera_x;
    ray->map.x = (int)ray->pos.x;
    ray->map.y = (int)ray->pos.y;
    ray->delta_dist.x = get_delta_dist(ray->dir.x);
    ray->delta_dist.y = get_delta_dist(ray->dir.y);
}

void set_ray_steps(raycast_t *ray)
{
    if (ray->dir.x < 0) {
        ray->step.x = -1;
        ray->side_dist.x = (ray->pos.x - ray->map.x) * ray->delta_dist.x;
    } else {
        ray->step.x = 1;
        ray->side_dist.x = (ray->map.x + 1 - ray->pos.x) * ray->delta_dist.x;
    }
    if (ray->dir.y < 0) {
        ray->step.y = -1;
        ray->side_dist.y = (ray->pos.y - ray->map.y) * ray->delta_dist.y;
    } else {
        ray->step.y = 1;
        ray->side_dist.y = (ray->map.y + 1 - ray->pos.y) * ray->delta_dist.y;
    }
}

void find_wall(raycast_t *ray, map_t *map)
{
    int hit = 0;

    while (hit == 0) {
        if (ray->side_dist.x < ray->side_dist.y) {
            ray->side_dist.x += ray->delta_dist.x;
            ray->map.x += ray->step.x;
            ray->side = 0;
        } else {
            ray->side_dist.y += ray->delta_dist.y;
            ray->map.y += ray->step.y;
            ray->side = 1;
        }
        if (map->tiles[ray->map.y][ray->map.x] > 0)
            hit = 1;
    }
    if (ray->side == 0)
        ray->wall_dist = (ray->side_dist.x - ray->delta_dist.x);
    else
        ray->wall_dist = (ray->side_dist.y - ray->delta_dist.y);
}

void calculate_line(raycast_t *ray)
{
    ray->line_height = (int)(720 / ray->wall_dist);
    ray->draw_start = 360 - ray->line_height / 2;
    ray->draw_end = 360 + ray->line_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    if (ray->draw_end >= 720)
        ray->draw_end = 719;
}
