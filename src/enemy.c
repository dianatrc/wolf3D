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

static void draw_enemy_column(wolf_t *wolf, int x, float trans_y, int height)
{
    int start = 360 - height / 2;
    int end = 360 + height / 2;
    sfColor color = sfRed;

    if (start < 0)
        start = 0;
    if (end >= 720)
        end = 719;
    if (trans_y > 0 && trans_y < wolf->buffer->d_buffer[x])
        for (int y = start; y <= end; y++)
            put_pixel(wolf->buffer, &color, x, y);
}

void draw_enemies(wolf_t *wolf)
{
    sfVector2f trans;
    int screen_x;
    int height;
    int bounds[2];

    for (int i = 0; i < wolf->enemy_count; i++) {
        project_enemy(wolf, &wolf->enemies[i], &trans);
        if (trans.y <= 0)
            continue;
        screen_x = (int)((1280 / 2) * (1 + trans.x / trans.y));
        height = abs((int)(720 / trans.y));
        bounds[0] = screen_x - height / 2;
        bounds[1] = screen_x + height / 2;
        if (bounds[0] < 0)
            bounds[0] = 0;
        if (bounds[1] >= 1280)
            bounds[1] = 1279;
        for (int x = bounds[0]; x <= bounds[1]; x++)
            draw_enemy_column(wolf, x, trans.y, height);
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
    float speed = 1.5f * dt;
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
