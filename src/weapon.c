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
    weapon->is_shooting = 0;
    weapon->shoot_time = 0.0f;
    weapon->duration = 0.2f;
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

static float calculate_kickback(weapon_t *weapon)
{
    float half_duration = weapon->duration / 2.0f;
    float progress = 0.0f;
    float kickback = 0.0f;

    if (weapon->shoot_time < half_duration) {
        progress = weapon->shoot_time / half_duration;
        kickback = progress * 40.0f;
        return kickback;
    }
    progress = (weapon->shoot_time - half_duration) / half_duration;
    kickback = 40.0f - progress * 40.0f;
    return kickback;
}

static void reset_weapon_state(weapon_t *weapon)
{
    weapon->is_shooting = 0;
    weapon->shoot_time = 0.0f;
    sfSprite_setPosition(weapon->sprite, weapon->rest_pos);
}

void update_weapon(weapon_t *weapon, float dt)
{
    float kickback = 0.0f;
    sfVector2f current_pos;

    if (!weapon || weapon->is_shooting == 0)
        return;
    weapon->shoot_time += dt;
    if (weapon->shoot_time >= weapon->duration) {
        reset_weapon_state(weapon);
        return;
    }
    kickback = calculate_kickback(weapon);
    current_pos = weapon->rest_pos;
    current_pos.y -= kickback;
    sfSprite_setPosition(weapon->sprite, current_pos);
}
