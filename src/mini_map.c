/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Mini-map creation and handling
*/

#include "include/wolf3d.h"

void init_minimap(wolf_t *wolf)
{
    float width_ratio = 0.25f * (720.0f / 1280.0f);
    sfFloatRect viewport = {1.0f - width_ratio - 0.02f,
        0.75f, width_ratio, 0.2f};

    wolf->minimap = sfView_create();
    if (!wolf->minimap)
        return;
    sfView_setViewport(wolf->minimap, viewport);
}

static void draw_minimap_line(sfRenderWindow *window, wolf_t *wolf,
    sfRectangleShape *tile, int y)
{
    for (int x = 0; x < wolf->map->map_width; x++)
        if (wolf->map->tiles[y][x] > 0) {
            sfRectangleShape_setPosition(tile,
                (sfVector2f){(float)x, (float)y});
            sfRectangleShape_setFillColor(tile, sfBlack);
            sfRenderWindow_drawRectangleShape(window, tile, NULL);
        }
}

static void draw_minimap_grid(sfRenderWindow *window, wolf_t *wolf)
{
    sfRectangleShape *tile = sfRectangleShape_create();

    if (!tile)
        return;
    sfRectangleShape_setSize(tile, (sfVector2f){(float)wolf->map->map_width,
            (float)wolf->map->map_height});
    sfRectangleShape_setPosition(tile, (sfVector2f){0.0f, 0.0f});
    sfRectangleShape_setFillColor(tile, sfWhite);
    sfRenderWindow_drawRectangleShape(window, tile, NULL);
    sfRectangleShape_setSize(tile, (sfVector2f){0.95f, 0.95f});
    for (int y = 0; y < wolf->map->map_height; y++)
        draw_minimap_line(window, wolf, tile, y);
    sfRectangleShape_destroy(tile);
}

static void draw_player_point(sfRenderWindow *window, sfVector2f *pos)
{
    sfCircleShape *player_point = sfCircleShape_create();

    if (!player_point)
        return;
    sfCircleShape_setRadius(player_point, 0.4f);
    sfCircleShape_setOrigin(player_point, (sfVector2f){0.4f, 0.4f});
    sfCircleShape_setPosition(player_point, *pos);
    sfCircleShape_setFillColor(player_point, sfRed);
    sfRenderWindow_drawCircleShape(window, player_point, NULL);
    sfCircleShape_destroy(player_point);
}

static void draw_enemy_point(sfRenderWindow *window, sfVector2f *pos)
{
    sfCircleShape *enemy_point = sfCircleShape_create();

    if (!enemy_point)
        return;
    sfCircleShape_setRadius(enemy_point, 0.4f);
    sfCircleShape_setOrigin(enemy_point, (sfVector2f){0.4f, 0.4f});
    sfCircleShape_setPosition(enemy_point, *pos);
    sfCircleShape_setFillColor(enemy_point, sfBlue);
    sfRenderWindow_drawCircleShape(window, enemy_point, NULL);
    sfCircleShape_destroy(enemy_point);
}

void draw_minimap(sfRenderWindow *window, wolf_t *wolf)
{
    const sfView *default_view = sfRenderWindow_getDefaultView(window);
    sfVector2f map_center = {(float)wolf->map->map_width / 2.0f,
        (float)wolf->map->map_height / 2.0f};
    sfVector2f view_size = {(float)wolf->map->map_width + 2.0f,
        (float)wolf->map->map_height + 2.0f};

    if (!window || !wolf || !wolf->minimap)
        return;
    sfView_setCenter(wolf->minimap, map_center);
    sfView_setSize(wolf->minimap, view_size);
    sfRenderWindow_setView(window, wolf->minimap);
    draw_minimap_grid(window, wolf);
    draw_enemy_point(window, &wolf->enemies[0].pos);
    draw_player_point(window, &wolf->player->pos);
    sfRenderWindow_setView(window, default_view);
}
