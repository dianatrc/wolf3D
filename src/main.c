/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** wolf3d project
*/

#include "../include/wolf3d.h"

static void handle_events(sfRenderWindow **window, sfEvent *event,
    sfUint32 *style)
{
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(*window);
    if (event->type == sfEvtKeyPressed) {
        if (event->key.code == sfKeyF)
            window_fullscreen(window, style);
    }
}

static void game_loop(sfRenderWindow **window, sfUint32 *style)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(*window, &event)) {
        handle_events(window, &event, style);
    }
    if (!(*window))
        return;
    sfRenderWindow_clear(*window, sfBlack);
    sfRenderWindow_display(*window);
}

int main(void)
{
    sfUint32 style = sfClose | sfResize;
    sfRenderWindow *window = create_my_window(1280, 720, style);
    map_t *map = create_map(MAP_WIDTH, MAP_HEIGHT);

    if (!window || !map)
        return 84;
    while (sfRenderWindow_isOpen(window)) {
        game_loop(&window, &style);
        if (!window)
            return 84;
    }
    free_map(map);
    sfRenderWindow_destroy(window);
    return 0;
}
