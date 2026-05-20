/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Drawing functions
*/

#include "include/wolf3d.h"
#include "include/raycast.h"

void spawn_explosion(wolf_t *wolf, sfVector2f *pos, sfColor *color)
{
    int spawned = 0;

    for (int i = 0; i < wolf->particles->max; i++) {
        if (spawned >= 10)
            break;
        if (wolf->particles->pool[i].active == 0) {
            wolf->particles->pool[i].active = 1;
            wolf->particles->pool[i].pos = *pos;
            wolf->particles->pool[i].vel.x = ((rand() % 100) - 50)
                / 50.0f;
            wolf->particles->pool[i].vel.y = ((rand() % 100) - 50)
                / 50.0f;
            wolf->particles->pool[i].life = 0.5f;
            wolf->particles->pool[i].start_life = 0.5f;
            wolf->particles->pool[i].color = *color;
            spawned++;
        }
    }
}

void update_particles(wolf_t *wolf, float dt)
{
    for (int i = 0; i < wolf->particles->max; i++) {
        if (!wolf->particles->pool[i].active)
            continue;
        wolf->particles->pool[i].pos.x += wolf->particles->pool[i].vel.x * dt;
        wolf->particles->pool[i].pos.y += wolf->particles->pool[i].vel.y * dt;
        wolf->particles->pool[i].life -= dt;
        if (wolf->particles->pool[i].life <= 0.0f)
            wolf->particles->pool[i].active = 0;
    }
}

static void project_particle(wolf_t *wolf, particle_t *particle,
    sfVector2f *trans)
{
    float sprite_x = particle->pos.x - wolf->player->pos.x;
    float sprite_y = particle->pos.y - wolf->player->pos.y;
    float inv_det = 1.0f / (wolf->player->plane.x * wolf->player->dir.y
        - wolf->player->plane.y * wolf->player->dir.x);

    trans->x = inv_det * (wolf->player->dir.y * sprite_x
        - wolf->player->dir.x * sprite_y);
    trans->y = inv_det * (-wolf->player->plane.y * sprite_x
        + wolf->player->plane.x * sprite_y);
}

static void draw_particle_square(framebuffer_t *buffer, sfVector2i *pos,
    int size, sfColor *color)
{
    int start_x = pos->x - size / 2;
    int end_x = pos->x + size / 2;
    int start_y = pos->y - size / 2;
    int end_y = pos->y + size / 2;

    if (start_x < 0)
        start_x = 0;
    if (end_x >= 1280)
        end_x = 1279;
    if (start_y < 0)
        start_y = 0;
    if (end_y >= 720)
        end_y = 719;
    for (int y = start_y; y <= end_y; y++)
        for (int x = start_x; x <= end_x; x++)
            put_pixel(buffer, color, x, y);
}

static void render_particle(wolf_t *wolf, particle_t *particle,
    sfVector2f *trans)
{
    int screen_x = (int)((1280 / 2) * (1 + trans->x / trans->y));
    int size = abs((int)(20 / trans->y));
    sfVector2i pos;

    if (screen_x > 0 && screen_x < 1280
        && trans->y < wolf->buffer->d_buffer[screen_x]) {
        pos = (sfVector2i){screen_x, 360};
        draw_particle_square(wolf->buffer, &pos, size, &particle->color);
    }
}

void draw_particles(wolf_t *wolf)
{
    sfVector2f trans;

    for (int i = 0; i < wolf->particles->max; i++) {
        if (!wolf->particles->pool[i].active)
            continue;
        project_particle(wolf, &wolf->particles->pool[i], &trans);
        if (trans.y > 0)
            render_particle(wolf, &wolf->particles->pool[i], &trans);
    }
}
