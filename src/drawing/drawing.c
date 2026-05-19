/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Drawing functions
*/

#include "include/wolf3d.h"
#include "include/raycast.h"

void apply_light(sfColor *color, float dist)
{
    float factor = 1.0f / (1.0f + (dist * dist * 0.07f));

    color->r *= factor;
    color->g *= factor;
    color->b *= factor;
}

void put_pixel(framebuffer_t *buffer, sfColor *color, int x, int y)
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

static void draw_background(framebuffer_t *buffer, wolf_t *wolf)
{
    for (int y = 0; y < buffer->height / 2; y++)
        draw_ceiling(buffer, wolf, y);
    for (int y = buffer->height / 2; y < buffer->height; y++)
        draw_floor(buffer, wolf, y);
}

static int get_texture_x(raycast_t *ray, int tex_w)
{
    float wall_x;
    int tex_x;

    if (ray->side == 0)
        wall_x = ray->pos.y + ray->wall_dist * ray->dir.y;
    else
        wall_x = ray->pos.x + ray->wall_dist * ray->dir.x;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (float)tex_w);
    if (ray->side == 0 && ray->dir.x > 0)
        tex_x = tex_w - tex_x - 1;
    if (ray->side == 1 && ray->dir.y < 0)
        tex_x = tex_w - tex_x - 1;
    if (tex_x < 0)
        return 0;
    if (tex_x >= tex_w)
        return (tex_w - 1);
    return tex_x;
}

static int get_texture_y(int tex_y, int tex_h)
{
    if (tex_y < 0)
        return 0;
    if (tex_y >= tex_h)
        return (tex_h - 1);
    return tex_y;
}

static void draw_wall(wolf_t *wolf, raycast_t *ray, int tex_data[3],
    sfVector2i *screen)
{
    sfColor wall_color;
    int tex_y = get_texture_y(tex_data[1], tex_data[2]);

    wall_color = sfImage_getPixel(wolf->wall_img, tex_data[0], tex_y);
    if (ray->side == 1) {
        wall_color.r /= 1.5f;
        wall_color.g /= 1.5f;
        wall_color.b /= 1.5f;
    }
    if (wolf->flash_on)
        apply_light(&wall_color, ray->wall_dist);
    put_pixel(wolf->buffer, &wall_color, screen->x, screen->y);
}

static void draw_column(wolf_t *wolf, raycast_t *ray, int screen_x)
{
    sfVector2u tex_size = sfImage_getSize(wolf->wall_img);
    float factor = 1.0f * tex_size.y / ray->line_height;
    float tex_pos = (ray->draw_start - 360 + ray->line_height / 2) * factor;
    int tex_data[3];
    sfVector2i screen;

    tex_data[0] = get_texture_x(ray, tex_size.x);
    tex_data[2] = tex_size.y;
    screen.x = screen_x;
    for (int y = ray->draw_start; y <= ray->draw_end; y++) {
        tex_data[1] = (int)tex_pos;
        screen.y = y;
        draw_wall(wolf, ray, tex_data, &screen);
        tex_pos += factor;
    }
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
        wolf->buffer->d_buffer[x] = ray.wall_dist;
        draw_column(wolf, &ray, x);
    }
}
