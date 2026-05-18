/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Weapon creation
*/

#include "../include/wolf3d.h"

static void init_weapon_helper(weapon_t *weapon)
{
    weapon->is_shooting = 0;
    weapon->shoot_time = 0.0f;
    weapon->duration = 0.2f;
    weapon->bobbing_time = 0.0f;
}

weapon_t *init_weapon(void)
{
    weapon_t *weapon = malloc(sizeof(weapon_t));
    sfFloatRect bounds;

    if (!weapon)
        return NULL;
    init_weapon_helper(weapon);
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

static void draw_bullet_line(sfRenderWindow *window, weapon_t *weapon)
{
    sfVertex lines[2];
    sfVector2f weapon_pos;
    float half_duration = 0.0f;

    if (!window || !weapon || weapon->is_shooting == 0)
        return;
    half_duration = weapon->duration / 2.0f;
    if (weapon->shoot_time > half_duration)
        return;
    weapon_pos = sfSprite_getPosition(weapon->sprite);
    lines[0].position = (sfVector2f){620.0f, weapon_pos.y + 40.0f};
    lines[0].color = sfYellow;
    lines[1].position = (sfVector2f){620.0f, 200.0f};
    lines[1].color = sfTransparent;
    sfRenderWindow_drawPrimitives(window, lines, 2, sfLines, NULL);
}

void draw_weapon(sfRenderWindow *window, weapon_t *weapon)
{
    if (!window || !weapon)
        return;
    draw_bullet_line(window, weapon);
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

static void apply_bobbing(weapon_t *weapon, float dt)
{
    sfVector2f bobbed_pos = weapon->rest_pos;
    float speed = 8.0f;

    if (sfKeyboard_isKeyPressed(sfKeyW) || sfKeyboard_isKeyPressed(sfKeyS)) {
        if (sfKeyboard_isKeyPressed(sfKeyLShift))
            speed = 14.0f;
        weapon->bobbing_time += dt * speed;
        bobbed_pos.x += cos(weapon->bobbing_time) * 15.0f;
        bobbed_pos.y += sin(weapon->bobbing_time * 2.0f) * 8.0f;
    } else {
        weapon->bobbing_time = 0.0f;
    }
    sfSprite_setPosition(weapon->sprite, bobbed_pos);
}

void update_weapon(weapon_t *weapon, float dt)
{
    float kickback = 0.0f;
    sfVector2f current_pos;

    if (!weapon)
        return;
    if (weapon->is_shooting == 1) {
        weapon->shoot_time += dt;
        if (weapon->shoot_time >= weapon->duration) {
            reset_weapon_state(weapon);
            return;
        }
        kickback = calculate_kickback(weapon);
        current_pos = weapon->rest_pos;
        current_pos.y -= kickback;
        sfSprite_setPosition(weapon->sprite, current_pos);
    } else {
        apply_bobbing(weapon, dt);
    }
}
