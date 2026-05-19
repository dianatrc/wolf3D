/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Player health management
*/

#include "../include/wolf3d.h"

void damage_player(wolf_t *wolf, int damage)
{
    if (!wolf || !wolf->player)
        return;
    wolf->player->health -= damage;
    if (wolf->player->health <= 0)
        wolf->state = MENU;
}

static void draw_background(sfRenderWindow *window, sfRectangleShape *bg)
{
    sfRectangleShape_setSize(bg, (sfVector2f){200.0f, 25.0f});
    sfRectangleShape_setPosition(bg, (sfVector2f){50.0f, 650.0f});
    sfRectangleShape_setFillColor(bg, (sfColor){50, 50, 50, 200});
    sfRenderWindow_drawRectangleShape(window, bg, NULL);
}

static void draw_bar(sfRenderWindow *window, sfRectangleShape *bar,
    int health)
{
    float bar_width = 200.0f * ((float)health / 100.0f);

    if (bar_width <= 0.0f)
        return;
    sfRectangleShape_setSize(bar, (sfVector2f){bar_width, 25.0f});
    sfRectangleShape_setPosition(bar, (sfVector2f){50.0f, 650.0f});
    sfRectangleShape_setFillColor(bar, sfRed);
    sfRenderWindow_drawRectangleShape(window, bar, NULL);
}

void draw_health_bar(sfRenderWindow *window, wolf_t *wolf)
{
    sfRectangleShape *bg = sfRectangleShape_create();
    sfRectangleShape *bar = sfRectangleShape_create();

    if (!bg || !bar)
        return;
    draw_background(window, bg);
    draw_bar(window, bar, wolf->player->health);
    sfRectangleShape_destroy(bg);
    sfRectangleShape_destroy(bar);
}
