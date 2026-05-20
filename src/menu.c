/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Main menu functions
*/

#include "include/wolf3d.h"

static void create_objects(menu_t *menu)
{
    menu->title = sfText_create();
    menu->play_button = sfText_create();
    menu->settings = sfText_create();
    menu->exit_button = sfText_create();
    menu->save_button = sfText_create();
    menu->load_button = sfText_create();
    menu->g_to_menu = sfText_create();
    menu->vol_up = sfText_create();
    menu->vol_down = sfText_create();
    menu->s_to_menu = sfText_create();
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
    sfVector2f title_pos = {200, 200};
    sfVector2f play_pos = {300, 400};
    sfVector2f settings_pos = {350, 450};
    sfVector2f save_pos = {400, 500};
    sfVector2f load_pos = {450, 550};
    sfVector2f exit_pos = {500, 600};

    setup_text(menu->title, menu->font, "WOLFENSTEIN 3D", &title_pos);
    sfText_setCharacterSize(menu->title, 100);
    setup_text(menu->play_button, menu->font, "PLAY", &play_pos);
    setup_text(menu->settings, menu->font, "SETTINGS", &settings_pos);
    setup_text(menu->save_button, menu->font, "SAVE GAME", &save_pos);
    setup_text(menu->load_button, menu->font, "LOAD GAME", &load_pos);
    setup_text(menu->g_to_menu, menu->font, "MENU", &(sfVector2f){1150, 20});
    sfText_setCharacterSize(menu->g_to_menu, 30);
    setup_text(menu->exit_button, menu->font, "EXIT", &exit_pos);
    setup_text(menu->vol_up, menu->font, "VOL +", &(sfVector2f){500, 400});
    setup_text(menu->vol_down, menu->font, "VOL -", &(sfVector2f){500, 500});
    setup_text(menu->s_to_menu, menu->font, "MENU", &(sfVector2f){1150, 20});
    sfText_setCharacterSize(menu->s_to_menu, 30);
}

menu_t *init_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (!menu)
        return NULL;
    menu->font = sfFont_createFromFile("utils/arial.ttf");
    if (!menu->font)
        return NULL;
    create_objects(menu);
    menu_texts(menu);
    menu->volume = 20.0f;
    return menu;
}

void display_menu(sfRenderWindow *window, menu_t *menu)
{
    sfRenderWindow_clear(window, sfRed);
    sfRenderWindow_drawText(window, menu->title, NULL);
    sfRenderWindow_drawText(window, menu->play_button, NULL);
    sfRenderWindow_drawText(window, menu->settings, NULL);
    sfRenderWindow_drawText(window, menu->save_button, NULL);
    sfRenderWindow_drawText(window, menu->load_button, NULL);
    sfRenderWindow_drawText(window, menu->exit_button, NULL);
}

void display_settings(sfRenderWindow *window, menu_t *menu)
{
    sfRenderWindow_clear(window, sfRed);
    sfRenderWindow_drawText(window, menu->title, NULL);
    sfRenderWindow_drawText(window, menu->vol_up, NULL);
    sfRenderWindow_drawText(window, menu->vol_down, NULL);
    sfRenderWindow_drawText(window, menu->s_to_menu, NULL);
}

void destroy_menu(menu_t *menu)
{
    sfText_destroy(menu->title);
    sfText_destroy(menu->play_button);
    sfText_destroy(menu->settings);
    sfText_destroy(menu->save_button);
    sfText_destroy(menu->load_button);
    sfText_destroy(menu->exit_button);
    sfText_destroy(menu->g_to_menu);
    sfText_destroy(menu->vol_up);
    sfText_destroy(menu->vol_down);
    sfText_destroy(menu->s_to_menu);
    sfFont_destroy(menu->font);
    free(menu);
}
