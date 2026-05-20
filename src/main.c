/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** wolf3d project
*/

#include "../include/wolf3d.h"

static void game_state(wolf_t *wolf)
{
    sfTime time = sfClock_restart(wolf->clock);
    float dt = sfTime_asSeconds(time);

    if (wolf->player->damage_cooldown > 0.0f)
        wolf->player->damage_cooldown -= dt;
    render_wolf(wolf);
    sort_enemies(wolf);
    draw_enemies(wolf);
    sfTexture_updateFromPixels(wolf->texture, wolf->buffer->pixels,
        wolf->buffer->width, wolf->buffer->height, 0, 0);
    update_enemies(wolf, dt);
    move_player(wolf->player, wolf->map, dt);
    update_weapon(wolf->weapon, dt);
    sfRenderWindow_drawSprite(wolf->window, wolf->sprite, NULL);
    draw_weapon(wolf->window, wolf->weapon);
    draw_minimap(wolf->window, wolf);
    draw_health_bar(wolf->window, wolf);
    sfRenderWindow_drawText(wolf->window, wolf->menu->g_to_menu, NULL);
}

static void draw_game_state(wolf_t *wolf)
{
    switch (wolf->state) {
        case MENU:
            display_menu(wolf->window, wolf->menu);
            break;
        case GAME:
            if (wolf->player->health <= 0) {
                wolf->player->health = 100;
                wolf->player->damage_cooldown = 0.0f;
            }
            game_state(wolf);
            break;
        case GAME_OVER:
            sfRenderWindow_clear(wolf->window, sfRed);
            draw_game_over(wolf->window, wolf);
            if (sfKeyboard_isKeyPressed(sfKeySpace))
                wolf->state = MENU;
            break;
        case SETTINGS:
            display_settings(wolf->window, wolf->menu);
    }
}

static void game_loop(wolf_t *wolf)
{
    handle_events(wolf);
    if (!(wolf->window))
        return;
    sfRenderWindow_clear(wolf->window, sfBlack);
    draw_game_state(wolf);
    sfRenderWindow_display(wolf->window);
}

int main(void)
{
    wolf_t wolf;

    if (init_wolf(&wolf) == 84) {
        free_wolf(&wolf);
        return 84;
    }
    while (sfRenderWindow_isOpen(wolf.window))
        game_loop(&wolf);
    free_wolf(&wolf);
    return 0;
}
