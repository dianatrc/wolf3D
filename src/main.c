/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** wolf3d project
*/

#include "../include/wolf3d.h"

static int check_click(sfText *text, sfRenderWindow *window)
{
    sfFloatRect rect = sfText_getGlobalBounds(text);
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);

    if (sfFloatRect_contains(&rect, mouse_pos.x, mouse_pos.y))
        return 1;
    return 0;
}

static void handle_events(wolf_t *wolf, sfEvent *event)
{
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(wolf->window);
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyF)
            window_fullscreen(&(wolf->window), &wolf->style);
    }
    if (wolf->state == MENU && event->type == sfEvtMouseButtonPressed) {
        if (check_click(wolf->menu->play_button, wolf->window))
            wolf->state = GAME;
        if (check_click(wolf->menu->exit_button, wolf->window))
            sfRenderWindow_close(wolf->window);
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
    sfRenderWindow_clear(wolf->window, sfBlack);
    if (wolf->state == MENU)
        display_menu(wolf->window, wolf->menu);
    else {
        render_wolf(wolf);
        move_player(wolf->player, wolf->map, dt);
        sfRenderWindow_drawSprite(wolf->window, wolf->sprite, NULL);
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
