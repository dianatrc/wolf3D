/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** wolf3d project
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
        if (is_clicked(wolf, wolf->menu->g_to_menu))
            wolf->state = MENU;
        if (wolf->state == SETTINGS)
            settings_state(wolf);
    }
}

static void game_state(wolf_t *wolf)
{
    sfTime time = sfClock_restart(wolf->clock);
    float dt = sfTime_asSeconds(time);

    render_wolf(wolf);
    sort_enemies(wolf);
    draw_enemies(wolf);
    update_enemies(wolf, dt);
    move_player(wolf->player, wolf->map, dt);
    sfRenderWindow_drawSprite(wolf->window, wolf->sprite, NULL);
    sfRenderWindow_drawText(wolf->window, wolf->menu->g_to_menu, NULL);
}

static void game_loop(wolf_t *wolf)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(wolf->window, &event)) {
        handle_events(wolf, &event);
    }
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
