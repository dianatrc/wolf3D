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
    if (wolf->player->damage_cooldown > 0.0f)
        return;
    wolf->player->health -= damage;
    if (wolf->player->health <= 0)
        wolf->state = GAME_OVER;
    else
        wolf->player->damage_cooldown = 1.0f;
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

static void display_message(sfRenderWindow *window, sfFont *font)
{
    sfText *game_over = sfText_create();

    if (!game_over)
        return;
    sfText_setString(game_over, "GAME OVER");
    sfText_setFont(game_over, font);
    sfText_setCharacterSize(game_over, 100);
    sfText_setPosition(game_over, (sfVector2f){350.0f, 200.f});
    sfText_setFillColor(game_over, sfWhite);
    sfRenderWindow_drawText(window, game_over, NULL);
    sfText_destroy(game_over);
}

static void display_instruction(sfRenderWindow *window, sfFont *font)
{
    sfText *instruction = sfText_create();

    if (!instruction)
        return;
    sfText_setString(instruction, "Press SPACE to return to MENU");
    sfText_setFont(instruction, font);
    sfText_setCharacterSize(instruction, 50);
    sfText_setPosition(instruction, (sfVector2f){300.0f, 400.f});
    sfText_setFillColor(instruction, sfWhite);
    sfRenderWindow_drawText(window, instruction, NULL);
    sfText_destroy(instruction);
}

void draw_game_over(sfRenderWindow *window, wolf_t *wolf)
{
    if (!window || !wolf || !wolf->menu || !wolf->menu->font)
        return;
    display_message(window, wolf->menu->font);
    display_instruction(window, wolf->menu->font);
}
