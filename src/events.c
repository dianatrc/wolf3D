/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Events management
*/

#include "../include/wolf3d.h"

static int is_clicked(wolf_t *wolf, sfText *text)
{
    sfFloatRect rect = sfText_getGlobalBounds(text);
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(wolf->window);

    if (sfFloatRect_contains(&rect, mouse_pos.x, mouse_pos.y)) {
        sfSound_play(wolf->sounds->click);
        return 1;
    }
    return 0;
}

static void settings_state(wolf_t *wolf)
{
    if (is_clicked(wolf, wolf->menu->vol_up))
        update_volume(wolf, 10.0f);
    if (is_clicked(wolf, wolf->menu->vol_down))
        update_volume(wolf, -10.0f);
    if (is_clicked(wolf, wolf->menu->s_to_menu))
        wolf->state = MENU;
}

static void menu_state(wolf_t *wolf)
{
    if (is_clicked(wolf, wolf->menu->play_button))
        wolf->state = GAME;
    if (is_clicked(wolf, wolf->menu->exit_button))
        sfRenderWindow_close(wolf->window);
    if (is_clicked(wolf, wolf->menu->save_button))
        save_game(wolf, "saved.txt");
    if (is_clicked(wolf, wolf->menu->load_button))
        if (load_save(wolf, "saved.txt") == 0)
            wolf->state = GAME;
    if (is_clicked(wolf, wolf->menu->settings))
        wolf->state = SETTINGS;
}

static void handle_key_events(wolf_t *wolf, sfKeyCode code)
{
    if (code == sfKeyF)
        window_fullscreen(&(wolf->window), &wolf->style);
    if (code == sfKeyL)
        wolf->flash_on = !wolf->flash_on;
    if (code == sfKeyEscape)
        wolf->state = MENU;
    if (code == sfKeySpace && wolf->state == GAME &&
        wolf->weapon->is_shooting == 0) {
        wolf->weapon->is_shooting = 1;
        wolf->weapon->shoot_time = 0.0f;
        sfSound_play(wolf->sounds->shoot);
    }
}

static void handle_mouse_events(wolf_t *wolf)
{
    if (wolf->state == MENU)
        menu_state(wolf);
    if (is_clicked(wolf, wolf->menu->g_to_menu))
        wolf->state = MENU;
    if (wolf->state == SETTINGS)
        settings_state(wolf);
}

void handle_events(wolf_t *wolf)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(wolf->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(wolf->window);
        if (event.type == sfEvtKeyPressed)
            handle_key_events(wolf, event.key.code);
        if (event.type == sfEvtMouseButtonPressed)
            handle_mouse_events(wolf);
    }
}
