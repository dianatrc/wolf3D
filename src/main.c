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

static void menu_state(wolf_t *wolf)
{
    if (check_click(wolf->menu->play_button, wolf->window)) {
        sfSound_play(wolf->sounds->click);
        wolf->state = GAME;
    }
    if (check_click(wolf->menu->exit_button, wolf->window)) {
        sfSound_play(wolf->sounds->click);
        sfRenderWindow_close(wolf->window);
    }
    if (check_click(wolf->menu->save_button, wolf->window)) {
        sfSound_play(wolf->sounds->click);
        save_game(wolf, "saved.txt");
    }
    if (check_click(wolf->menu->load_button, wolf->window)) {
        sfSound_play(wolf->sounds->click);
        if (load_save(wolf, "saved.txt") == 0)
            wolf->state = GAME;
    }
}

static void handle_events(wolf_t *wolf, sfEvent *event)
{
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(wolf->window);
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyF)
            window_fullscreen(&(wolf->window), &wolf->style);
        if (event->key.code == sfKeyL)
            wolf->flash_on = !wolf->flash_on;
        if (event->key.code == sfKeyEscape)
            wolf->state = MENU;
    }
    if (event->type == sfEvtMouseButtonPressed) {
        if (wolf->state == MENU)
            menu_state(wolf);
        if (wolf->state == GAME
            && check_click(wolf->menu->to_menu, wolf->window)) {
            sfSound_play(wolf->sounds->click);
            wolf->state = MENU;
        }
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
    if (wolf->state == MENU) {
        sfRenderWindow_setMouseCursorVisible(wolf->window, sfTrue);
        display_menu(wolf->window, wolf->menu);
    } else {
        render_wolf(wolf);
        move_player(wolf->player, wolf->map, dt);
        sfRenderWindow_drawSprite(wolf->window, wolf->sprite, NULL);
        sfRenderWindow_drawText(wolf->window, wolf->menu->to_menu, NULL);
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
