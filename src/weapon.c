/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Weapon creation
*/

#include "../include/wolf3d.h"

weapon_t *init_weapon(void)
{
    weapon_t *weapon = malloc(sizeof(weapon_t));
    sfFloatRect bounds;

    if (!weapon)
        return NULL;
    weapon->texture = sfTexture_createFromFile("utils/weapon.png", NULL);
    weapon->sprite = sfSprite_create();
    if (!weapon->texture || !weapon->sprite) {
        free(weapon);
        return NULL;
    }
    sfSprite_setTexture(weapon->sprite, weapon->texture, sfTrue);
    bounds = sfSprite_getGlobalBounds(weapon->sprite);
    weapon->rest_pos.x = 640.0f - (bounds.width / 2.0f);
    weapon->rest_pos.y = 720.0f - bounds.height;
    sfSprite_setPosition(weapon->sprite, weapon->rest_pos);
    return weapon;
}

void draw_weapon(sfRenderWindow *window, weapon_t *weapon)
{
    if (!window || !weapon)
        return;
    sfRenderWindow_drawSprite(window, weapon->sprite, NULL);
}

void destroy_weapon(weapon_t *weapon)
{
    if (!weapon)
        return;
    if (weapon->sprite)
        sfSprite_destroy(weapon->sprite);
    if (weapon->texture)
        sfTexture_destroy(weapon->texture);
    free(weapon);
}
