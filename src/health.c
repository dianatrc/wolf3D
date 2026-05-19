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
