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
    sfRenderWindow_drawText(wolf->window, wolf->menu->g_to_menu, NULL);
}

static void game_loop(wolf_t *wolf)
{
    handle_events(wolf);
    if (!(wolf->window))
        return;
    sfRenderWindow_clear(wolf->window, sfBlack);
    switch (wolf->state) {
        case MENU:
            display_menu(wolf->window, wolf->menu);
            break;
        case GAME:
            game_state(wolf);
            break;
        case SETTINGS:
            display_settings(wolf->window, wolf->menu);
            break;
    }
    sfRenderWindow_display(wolf->window);
}

int main(void)
{
    wolf_t wolf;

    if (init_wolf(&wolf) == 84) {
        free_wolf(&wolf);
        return 84;
    }
    while (sfRenderWindow_isOpen(wolf.window)) {
        game_loop(&wolf);
    }
    free_wolf(&wolf);
    return 0;
}
