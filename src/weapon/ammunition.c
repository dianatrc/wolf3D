/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Ammunition bar display
*/

#include "include/wolf3d.h"

static void draw_ammo_background(sfRenderWindow *window, sfRectangleShape *bg)
{
    sfRectangleShape_setSize(bg, (sfVector2f){200.0f, 25.0f});
    sfRectangleShape_setPosition(bg, (sfVector2f){50.0f, 620.0f});
    sfRectangleShape_setFillColor(bg, (sfColor){50, 50, 50, 200});
    sfRenderWindow_drawRectangleShape(window, bg, NULL);
}

static void draw_ammo_bar(sfRenderWindow *window, sfRectangleShape *bar,
    int ammunition)
{
    float bar_width = 200.0f * ((float)ammunition / 20.0f);

    if (bar_width <= 0.0f)
        return;
    sfRectangleShape_setSize(bar, (sfVector2f){bar_width, 25.0f});
    sfRectangleShape_setPosition(bar, (sfVector2f){50.0f, 620.0f});
    sfRectangleShape_setFillColor(bar, sfBlue);
    sfRenderWindow_drawRectangleShape(window, bar, NULL);
}

void draw_ammunition(sfRenderWindow *window, wolf_t *wolf)
{
    sfRectangleShape *bg = sfRectangleShape_create();
    sfRectangleShape *bar = sfRectangleShape_create();

    if (!bg || !bar)
        return;
    draw_ammo_background(window, bg);
    draw_ammo_bar(window, bar, wolf->weapon->ammunition);
    sfRectangleShape_destroy(bg);
    sfRectangleShape_destroy(bar);
}
