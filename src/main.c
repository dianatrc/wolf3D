/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** wolf3d project
*/

#include "../include/wolf3d.h"

static void handle_events(wolf_t *wolf, sfEvent *event)
{
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(wolf->window);
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyF)
            window_fullscreen(&(wolf->window), &wolf->style);
    }
}

static void game_loop(wolf_t *wolf)
{
    sfEvent event;
    sfTime time = sfClock_restart(wolf->clock);
    float dt = sfTime_asSeconds(time);

    while (sfRenderWindow_pollEvent(wolf->window, &event)) {
        handle_events(wolf, &event);
    }
    if (!(wolf->window))
        return;
    move_player(wolf->player, wolf->map, dt);
    sfRenderWindow_clear(wolf->window, sfBlack);
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
