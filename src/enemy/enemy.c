/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Enemy functions
*/

#include "include/wolf3d.h"
#include "include/raycast.h"

static void project_enemy(wolf_t *wolf, enemy_t *enemy, sfVector2f *trans)
{
    float sprite_x = enemy->pos.x - wolf->player->pos.x;
    float sprite_y = enemy->pos.y - wolf->player->pos.y;
    float inv_det = 1.0f / (wolf->player->plane.x * wolf->player->dir.y
        - wolf->player->plane.y * wolf->player->dir.x);

    trans->x = inv_det * (wolf->player->dir.y * sprite_x
        - wolf->player->dir.x * sprite_y);
    trans->y = inv_det * (-wolf->player->plane.y * sprite_x
        + wolf->player->plane.x * sprite_y);
}

static void put_enemy_pixel(wolf_t *wolf, sfVector2i *tex, sfVector2i *screen,
    int i)
{
    sfColor color = sfImage_getPixel(wolf->enemies[i].image, tex->x, tex->y);

    if (color.r > 150 && color.g < 100 && color.b > 150)
        return;
    if (color.r > 245 && color.g > 245 && color.b > 245)
        return;
    if (wolf->flash_on)
        apply_light(&color, wolf->enemies[i].dist);
    put_pixel(wolf->buffer, &color, screen->x, screen->y);
}

static void draw_enemy_pixel(wolf_t *wolf, sfVector2i *xs, sfVector2i *y_pos,
    int i)
{
    sfVector2u tex_size = sfImage_getSize(wolf->enemies[i].image);
    sfVector2i tex = {xs->y, y_pos->y};
    sfVector2i screen = {xs->x, y_pos->x};

    if (tex.y < 0)
        tex.y = 0;
    if (tex.y >= (int)tex_size.y)
        tex.y = tex_size.y - 1;
    put_enemy_pixel(wolf, &tex, &screen, i);
}

static void draw_enemy_column(wolf_t *wolf, sfVector2i *xs, int height, int i)
{
    int center_y = 360;
    int start = center_y - height / 2;
    int end = center_y + height / 2;
    sfVector2u tex_size = sfImage_getSize(wolf->enemies[i].image);
    float factor = 1.0f * (tex_size.y - 2) / height;
    float tex_pos;
    sfVector2i y_pos;

    if (start < 0)
        start = 0;
    if (end >= 720)
        end = 719;
    tex_pos = (start - (center_y - height / 2)) * factor;
    for (int y = start; y <= end; y++) {
        y_pos = (sfVector2i){y, (int)tex_pos};
        draw_enemy_pixel(wolf, xs, &y_pos, i);
        tex_pos += factor;
    }
}

static void render_enemy_column(wolf_t *wolf, int i, int x, sfVector2i *data)
{
    int height = data->x;
    int center_x = data->y;
    sfVector2u tex_size = sfImage_getSize(wolf->enemies[i].image);
    int frame_w = tex_size.x / wolf->enemies[i].total_frames;
    sfVector2i xs;

    xs.x = x;
    xs.y = ((x - (center_x - height / 2)) * frame_w / height) +
        (wolf->enemies[i].current_frame * frame_w);
    if (xs.y < 0)
        xs.y = 0;
    if (xs.y >= (int)tex_size.x)
        xs.y = tex_size.x - 1;
    draw_enemy_column(wolf, &xs, height, i);
}

static void render_enemy(wolf_t *wolf, int i, sfVector2f *trans)
{
    int screen_x = (int)((1280 / 2) * (1 + trans->x / trans->y));
    int height = abs((int)(720 / trans->y));
    sfVector2i bounds;
    sfVector2i data = {height, screen_x};

    if (height == 0)
        return;
    bounds.x = screen_x - height / 2;
    bounds.y = screen_x + height / 2;
    if (bounds.x < 0)
        bounds.x = 0;
    if (bounds.y >= 1280)
        bounds.y = 1279;
    for (int x = bounds.x; x <= bounds.y; x++) {
        if (trans->y < wolf->buffer->d_buffer[x])
            render_enemy_column(wolf, i, x, &data);
    }
}

void draw_enemies(wolf_t *wolf)
{
    sfVector2f trans;

    for (int i = 0; i < wolf->enemy_count; i++) {
        project_enemy(wolf, &wolf->enemies[i], &trans);
        if (trans.y <= 0)
            continue;
        render_enemy(wolf, i, &trans);
    }
}
