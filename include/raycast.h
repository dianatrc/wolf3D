/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Header file for raycasting
*/

#ifndef RAYCAST_H_
    #define RAYCAST_H_

    #include "wolf3d.h"

typedef struct {
    sfVector2f pos;
    sfVector2f dir;
    sfVector2i map;
    sfVector2f side_dist;
    sfVector2f delta_dist;
    sfVector2i step;
    int side;
    float wall_dist;
    int line_height;
    int draw_start;
    int draw_end;
} raycast_t;

// raycast.c
void init_ray(raycast_t *ray, player_t *player, int x);
void set_ray_steps(raycast_t *ray);
void find_wall(raycast_t *ray, map_t *map);
void calculate_line(raycast_t *ray);

#endif
