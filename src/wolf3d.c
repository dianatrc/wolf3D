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
    buffer->d_buffer = malloc(sizeof(float) * width);
    if (!buffer->pixels || !buffer->d_buffer) {
        if (buffer->pixels)
            free(buffer->pixels);
        if (buffer->d_buffer)
            free(buffer->d_buffer);
        free(buffer);
        return NULL;
    }
    return buffer;
}

static int init_helper(wolf_t *wolf)
{
    wolf->menu = init_menu();
    wolf->style = sfClose | sfResize;
    wolf->state = MENU;
    wolf->flash_on = 0;
    wolf->enemy_count = 1;
    wolf->enemies = malloc(sizeof(enemy_t) * wolf->enemy_count);
    wolf->wall_img = sfImage_createFromFile("utils/wall.bmp");
    wolf->ceiling_img = sfImage_createFromFile("utils/sky.bmp");
    wolf->floor_img = sfImage_createFromFile("utils/grass.bmp");
    wolf->weapon = init_weapon();
    if (!wolf->enemies || !wolf->wall_img || !wolf->ceiling_img
        || !wolf->floor_img || !wolf->menu || !wolf->weapon)
        return 1;
    wolf->enemies[0].pos = (sfVector2f){4.5f, 1.5f};
    wolf->enemies[0].health = 100;
    wolf->enemies[0].image = sfImage_createFromFile("utils/enemy.bmp");
    return 0;
}

int init_wolf(wolf_t *wolf)
{
    if (init_helper(wolf) == 1)
        return 84;
    wolf->window = create_my_window(1280, 720, wolf->style);
    wolf->map = load_map("map.legend");
    wolf->player = create_player();
    wolf->clock = sfClock_create();
    wolf->buffer = create_framebuffer(1280, 720);
    wolf->texture = sfTexture_create(1280, 720);
    sfTexture_setSmooth(wolf->texture, sfTrue);
    wolf->sprite = sfSprite_create();
    sfSprite_setTexture(wolf->sprite, wolf->texture, sfTrue);
    wolf->sounds = init_sounds();
    if (!wolf->window || !wolf->map || !wolf->player || !wolf->clock
        || !wolf->buffer || !wolf->texture
        || !wolf->sprite || !wolf->sounds || !wolf->weapon) {
        free_wolf(wolf);
        return 84;
    }
    init_minimap(wolf);
    return 0;
}

static void free_buffer(framebuffer_t *buffer)
{
    free(buffer->pixels);
    free(buffer->d_buffer);
    free(buffer);
}

static void free_helper(wolf_t *wolf)
{
    if (wolf->enemies)
        free(wolf->enemies);
    if (wolf->wall_img)
        sfImage_destroy(wolf->wall_img);
    if (wolf->ceiling_img)
        sfImage_destroy(wolf->ceiling_img);
    if (wolf->floor_img)
        sfImage_destroy(wolf->floor_img);
    if (wolf->weapon)
        destroy_weapon(wolf->weapon);
    if (wolf->minimap)
        sfView_destroy(wolf->minimap);
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
    if (wolf->buffer)
        free_buffer(wolf->buffer);
    if (wolf->texture)
        sfTexture_destroy(wolf->texture);
    if (wolf->sprite)
        sfSprite_destroy(wolf->sprite);
    if (wolf->sounds)
        free_sounds(wolf->sounds);
    free_helper(wolf);
}
