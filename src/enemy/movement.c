/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Enemy movement functions
*/

#include "include/wolf3d.h"
#include "include/raycast.h"

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

static void animate_enemy(enemy_t *enemy, float dt)
{
    enemy->anim_time += dt;
    if (enemy->anim_time > 0.2f) {
        enemy->anim_time = 0.0f;
        enemy->current_frame++;
        if (enemy->current_frame >= enemy->total_frames)
            enemy->current_frame = 0;
    }
}

void update_enemies(wolf_t *wolf, float dt)
{
    float dist = 0;

    for (int i = 0; i < wolf->enemy_count; i++) {
        dist = pow(wolf->player->pos.x - wolf->enemies[i].pos.x, 2) +
            pow(wolf->player->pos.y - wolf->enemies[i].pos.y, 2);
        animate_enemy(&wolf->enemies[i], dt);
        if (dist < 100.0f && dist > 0.5f)
            move_enemy(wolf, &wolf->enemies[i], dt);
        if (dist <= 0.5f)
            damage_player(wolf, 10);
    }
}
