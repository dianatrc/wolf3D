/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Drawing functions for the ceiling
*/

#include "include/wolf3d.h"
#include "include/raycast.h"

static void get_ceiling_pos(player_t *player, float dist, int x, float cell[2])
{
    float camera_x = (2 * x / (float)1280) - 1;
    float ray_dir_x = player->dir.x + player->plane.x * camera_x;
    float ray_dir_y = player->dir.y + player->plane.y * camera_x;

    cell[0] = player->pos.x + dist * ray_dir_x;
    cell[1] = player->pos.y + dist * ray_dir_y;
}

static void put_ceiling_pixel(wolf_t *wolf, int x, int y, sfVector2i *tex)
{
    sfColor color = sfImage_getPixel(wolf->ceiling_img, tex->x, tex->y);
    float dist = (float)wolf->buffer->height /
        (wolf->buffer->height - 2.0f * y);

    if (wolf->flash_on)
        apply_light(&color, dist);
    put_pixel(wolf->buffer, &color, x, y);
}

void draw_ceiling(framebuffer_t *buffer, wolf_t *wolf, int y)
{
    float dist = (float)buffer->height / (buffer->height - 2.0f * y);
    sfVector2u tex_size = sfImage_getSize(wolf->ceiling_img);
    float cell[2];
    sfVector2i tex;

    for (int x = 0; x < buffer->width; x++) {
        get_ceiling_pos(wolf->player, dist, x, cell);
        tex.x = (int)(cell[0] * tex_size.x) & (tex_size.x - 1);
        tex.y = (int)(cell[1] * tex_size.y) & (tex_size.y - 1);
        put_ceiling_pixel(wolf, x, y, &tex);
    }
}
