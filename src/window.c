/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Window creation and initialization
*/

#include "../include/wolf3d.h"

sfRenderWindow *create_my_window(int width, int height, sfUint32 style)
{
    sfRenderWindow *window;
    sfVideoMode video_mode;

    video_mode.width = width;
    video_mode.height = height;
    video_mode.bitsPerPixel = 32;
    window = sfRenderWindow_create(video_mode, "Wolf3D", style, NULL);
    if (!window)
        return NULL;
    sfRenderWindow_setFramerateLimit(window, 60);
    return window;
}

void window_fullscreen(sfRenderWindow **window, sfUint32 *style)
{
    sfRenderWindow_destroy(*window);
    if (*style == sfFullscreen)
        *style = sfClose | sfResize;
    else
        *style = sfFullscreen;
    *window = create_my_window(1280, 720, *style);
    if (!(*window))
        return;
}
