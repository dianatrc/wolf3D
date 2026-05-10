/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Drawing functions
*/

#include "../include/wolf3d.h"
#include "../include/raycast.h"

static void apply_light(sfColor *color, float dist)
{
    float factor = 1.0f / (1.0f + (dist * dist * 0.07f));

    color->r *= factor;
    color->g *= factor;
    color->b *= factor;
}

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

static void draw_ceiling(framebuffer_t *buffer, wolf_t *wolf, int y)
{
    float dist = (float)buffer->height / (buffer->height - 2.0f * y);
    sfColor color = sfBlue;

    if (wolf->flash_on)
        apply_light(&color, dist);
    for (int x = 0; x < buffer->width; x++)
        put_pixel(buffer, &color, x, y);
}

static void draw_floor(framebuffer_t *buffer, wolf_t *wolf, int y)
{
    float dist = (float)buffer->height / (2.0f * y - buffer->height);
    sfColor color = sfGreen;

    if (wolf->flash_on)
        apply_light(&color, dist);
    for (int x = 0; x < buffer->width; x++)
        put_pixel(buffer, &color, x, y);
}

static void draw_background(framebuffer_t *buffer, wolf_t *wolf)
{
    for (int y = 0; y < buffer->height / 2; y++)
        draw_ceiling(buffer, wolf, y);
    for (int y = buffer->height / 2; y < buffer->height; y++)
        draw_floor(buffer, wolf, y);
}

static void draw_wall(framebuffer_t *buffer, raycast_t *ray, int x,
    wolf_t *wolf)
{
    sfColor wall_color = sfBlack;

    if (ray->side == 1) {
        wall_color.r = 20;
        wall_color.g = 20;
        wall_color.b = 20;
    }
    if (wolf->flash_on)
        apply_light(&wall_color, ray->wall_dist);
    for (int y = ray->draw_start; y <= ray->draw_end; y++)
        put_pixel(buffer, &wall_color, x, y);
}

void render_wolf(wolf_t *wolf)
{
    raycast_t ray;

    draw_background(wolf->buffer, wolf);
    for (int x = 0; x < wolf->buffer->width; x++) {
        init_ray(&ray, wolf->player, x);
        set_ray_steps(&ray);
        find_wall(&ray, wolf->map);
        calculate_line(&ray);
        draw_wall(wolf->buffer, &ray, x, wolf);
    }
    sfTexture_updateFromPixels(wolf->texture, wolf->buffer->pixels,
        wolf->buffer->width, wolf->buffer->height, 0, 0);
}
