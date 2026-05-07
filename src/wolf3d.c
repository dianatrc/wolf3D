/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Functions for the wolf3d structure
*/

#include "../include/wolf3d.h"

static framebuffer_t *create_framebuffer(int width, int height)
{
    framebuffer_t *buffer = malloc(sizeof(framebuffer_t));

    if (!buffer)
        return NULL;
    buffer->width = width;
    buffer->height = height;
    buffer->pixels = malloc(width * height * 4 * sizeof(sfUint8));
    if (!buffer->pixels) {
        free(buffer);
        return NULL;
    }
    return buffer;
}

int init_wolf(wolf_t *wolf)
{
    wolf->style = sfClose | sfResize;
    wolf->window = create_my_window(1280, 720, wolf->style);
    wolf->map = load_map("map.legend");
    wolf->player = create_player();
    wolf->clock = sfClock_create();
    wolf->menu = init_menu();
    wolf->buffer = create_framebuffer(1280, 720);
    wolf->texture = sfTexture_create(1280, 720);
    wolf->sprite = sfSprite_create();
    if (!wolf->window || !wolf->map || !wolf->player ||
        !wolf->clock || !wolf->menu || !wolf->buffer ||
        !wolf->texture || !wolf->sprite)
        return 84;
    sfSprite_setTexture(wolf->sprite, wolf->texture, sfTrue);
    wolf->state = MENU;
    return 0;
}

void free_wolf(wolf_t *wolf)
{
    if (wolf->window)
        sfRenderWindow_destroy(wolf->window);
    if (wolf->map)
        free_map(wolf->map);
    if (wolf->player)
        free(wolf->player);
    if (wolf->clock)
        sfClock_destroy(wolf->clock);
    if (wolf->menu)
        destroy_menu(wolf->menu);
    if (wolf->buffer) {
        free(wolf->buffer->pixels);
        free(wolf->buffer);
    }
    if (wolf->texture)
        sfTexture_destroy(wolf->texture);
    if (wolf->sprite)
        sfSprite_destroy(wolf->sprite);
}
