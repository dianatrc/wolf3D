/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Enemy functions
*/

#include "../include/wolf3d.h"
#include "../include/raycast.h"

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

    if (color.r == 255 && color.g == 0 && color.b == 255)
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
    int floor_y = 360 + height / 2;
    int start = floor_y - height / 2;
    sfVector2u tex_size = sfImage_getSize(wolf->enemies[i].image);
    float factor = 1.0f * tex_size.y / (height / 2);
    float tex_pos;
    sfVector2i y_pos;

    if (start < 0)
        start = 0;
    tex_pos = (start - (floor_y - height / 2)) * factor;
    for (int y = start; y <= floor_y && y < 720; y++) {
        y_pos = (sfVector2i){y, (int)tex_pos};
        draw_enemy_pixel(wolf, xs, &y_pos, i);
        tex_pos += factor;
    }
}

static void render_enemy(wolf_t *wolf, int i, sfVector2f *trans)
{
    int screen_x = (int)((1280 / 2) * (1 + trans->x / trans->y));
    int height = abs((int)(720 / trans->y));
    sfVector2i xs;
    sfVector2i bounds;
    sfVector2u tex_size = sfImage_getSize(wolf->enemies[i].image);

    bounds.x = screen_x - height / 2;
    bounds.y = screen_x + height / 2;
    if (bounds.x < 0)
        bounds.x = 0;
    if (bounds.y >= 1280)
        bounds.y = 1279;
    for (int x = bounds.x; x <= bounds.y; x++) {
        xs.x = x;
        xs.y = (x - (screen_x - height / 2)) * tex_size.x / height;
        if (trans->y < wolf->buffer->d_buffer[x])
            draw_enemy_column(wolf, &xs, height, i);
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

static int compare_enemies(const void *a, const void *b)
{
    enemy_t *e1 = (enemy_t *)a;
    enemy_t *e2 = (enemy_t *)b;

    if (e1->dist < e2->dist)
        return 1;
    if (e1->dist > e2->dist)
        return -1;
    return 0;
}

void sort_enemies(wolf_t *wolf)
{
    for (int i = 0; i < wolf->enemy_count; i++) {
        wolf->enemies[i].dist =
            pow(wolf->player->pos.x - wolf->enemies[i].pos.x, 2) +
            pow(wolf->player->pos.y - wolf->enemies[i].pos.y, 2);
    }
    qsort(wolf->enemies, wolf->enemy_count, sizeof(enemy_t), compare_enemies);
}

static void move_enemy(wolf_t *wolf, enemy_t *enemy, float dt)
{
    float speed = 0.5f * dt;
    sfVector2f dir = {0};

    if (wolf->player->pos.x > enemy->pos.x)
        dir.x = speed;
    else
        dir.x = -speed;
    if (wolf->player->pos.y > enemy->pos.y)
        dir.y = speed;
    else
        dir.y = -speed;
    if (!is_wall(wolf->map, enemy->pos.x + dir.x, enemy->pos.y))
        enemy->pos.x += dir.x;
    if (!is_wall(wolf->map, enemy->pos.x, enemy->pos.y + dir.y))
        enemy->pos.y += dir.y;
}

void update_enemies(wolf_t *wolf, float dt)
{
    float dist = 0;

    for (int i = 0; i < wolf->enemy_count; i++) {
        dist = pow(wolf->player->pos.x - wolf->enemies[i].pos.x, 2) +
            pow(wolf->player->pos.y - wolf->enemies[i].pos.y, 2);
        if (dist < 100.0f && dist > 0.5f)
            move_enemy(wolf, &wolf->enemies[i], dt);
    }
}
