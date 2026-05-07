/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Drawing functions
*/

#include "../include/wolf3d.h"
#include "../include/raycast.h"

static void put_pixel(framebuffer_t *buffer, sfColor *color, int x, int y)
{
    int i = 0;

    if (x < 0 || x >= buffer->width || y < 0 || y >= buffer->height)
        return;
    i = (y * buffer->width + x) * 4;
    buffer->pixels[i] = color->r;
    buffer->pixels[i + 1] = color->g;
    buffer->pixels[i + 2] = color->b;
    buffer->pixels[i + 3] = color->a;
}

static void draw_background(framebuffer_t *buffer, sfColor *ceiling,
    sfColor *floor)
{
    for (int y = 0; y < buffer->height / 2; y++)
        for (int x = 0; x < buffer->width; x++)
            put_pixel(buffer, ceiling, x, y);
    for (int y = buffer->height / 2; y < buffer->height; y++)
        for (int x = 0; x < buffer->width; x++)
            put_pixel(buffer, floor, x, y);
}

static void draw_wall(framebuffer_t *buffer, raycast_t *ray, int x)
{
    sfColor wall_color = sfBlack;

    if (ray->side == 1) {
        wall_color.r = 20;
        wall_color.g = 20;
        wall_color.b = 20;
    }
    for (int y = ray->draw_start; y <= ray->draw_end; y++)
        put_pixel(buffer, &wall_color, x, y);
}

void render_wolf(wolf_t *wolf)
{
    raycast_t ray;
    sfColor ceiling = sfBlue;
    sfColor floor = sfGreen;

    draw_background(wolf->buffer, &ceiling, &floor);
    for (int x = 0; x < wolf->buffer->width; x++) {
        init_ray(&ray, wolf->player, x);
        set_ray_steps(&ray);
        find_wall(&ray, wolf->map);
        calculate_line(&ray);
        draw_wall(wolf->buffer, &ray, x);
    }
    sfTexture_updateFromPixels(wolf->texture, wolf->buffer->pixels,
        wolf->buffer->width, wolf->buffer->height, 0, 0);
}
