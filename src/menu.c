/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Main menu functions
*/

#include "../include/wolf3d.h"

static void create_objects(menu_t *menu)
{
    menu->title = sfText_create();
    menu->play_button = sfText_create();
    menu->settings = sfText_create();
    menu->exit_button = sfText_create();
    menu->sprite = sfSprite_create();
}

static void setup_text(sfText *text, sfFont *font,
    const char *string, sfVector2f *pos)
{
    sfText_setString(text, string);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 50);
    sfText_setPosition(text, *pos);
    sfText_setColor(text, sfWhite);
}

static void menu_texts(menu_t *menu)
{
    const char *title = "WOLFENSTEIN 3D";
    const char *play = "PLAY";
    const char *settings = "SETTINGS";
    const char *exit = "EXIT";
    sfVector2f title_pos = {400, 100};
    sfVector2f play_pos = {350, 200};
    sfVector2f settings_pos = {400, 200};
    sfVector2f exit_pos = {450, 200};

    setup_text(menu->title, menu->font, title, &title_pos);
    sfText_setCharacterSize(menu->title, 100);
    setup_text(menu->play_button, menu->font, play, &play_pos);
    setup_text(menu->settings, menu->font, settings, &settings_pos);
    setup_text(menu->exit_button, menu->font, exit, &exit_pos);
}

menu_t *init_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (!menu)
        return NULL;
    menu->font = sfFont_createFromFile("utils/arial.ttf");
    menu->texture = sfTexture_createFromFile("utils/menu_background.jpg", NULL);
    if (!menu->font || !menu->texture)
        return NULL;
    create_objects(menu);
    sfSprite_setTexture(menu->sprite, menu->texture, sfTrue);
    menu_texts(menu);
    return menu;
}

void display_menu(sfRenderWindow *window, menu_t *menu)
{
    sfRenderWindow_drawSprite(window, menu->sprite, NULL);
    sfRenderWindow_drawText(window, menu->title, NULL);
    sfRenderWindow_drawText(window, menu->play_button, NULL);
    sfRenderWindow_drawText(window, menu->settings, NULL);
    sfRenderWindow_drawText(window, menu->exit_button, NULL);
}

void destroy_menu(menu_t *menu)
{
    sfText_destroy(menu->title);
    sfText_destroy(menu->play_button);
    sfText_destroy(menu->settings);
    sfText_destroy(menu->exit_button);
    sfFont_destroy(menu->font);
    sfSprite_destroy(menu->sprite);
    sfTexture_destroy(menu->texture);
    free(menu);
}
