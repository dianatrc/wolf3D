/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Header file for functions and for includes
*/

#ifndef WOLFENSTEIN3D_H_
    #define WOLFENSTEIN3D_H_

    #include <SFML/Graphics.h>
    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Window/VideoMode.h>
    #include <SFML/Window/Event.h>
    #include <SFML/Window/Mouse.h>
    #include <SFML/Audio.h>
    #include <SFML/Audio/Sound.h>
    #include <SFML/Audio/SoundBuffer.h>
    #include <math.h>
    #include <stdlib.h>
    #include <stdio.h>

typedef struct {
    int map_width;
    int map_height;
    int **tiles;
} map_t;

typedef struct {
    sfVector2f pos;
    sfVector2f dir;
    sfVector2f plane;
    float speed;
    float rot_speed;
} player_t;

typedef struct {
    int width;
    int height;
    sfUint8 *pixels;
} framebuffer_t;

typedef enum {
    MENU,
    GAME
} game_state_t;

typedef struct {
    sfFont *font;
    sfText *title;
    sfText *play_button;
    sfText *settings;
    sfText *exit_button;
    sfSprite *sprite;
    sfTexture *texture;
} menu_t;

typedef struct {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f rest_pos;
    float rest_rot;
    sfVector2f aim_pos;
    float aim_rot;
    int is_aiming;
} weapon_t;

typedef struct {
    sfRenderWindow *window;
    sfUint32 style;
    sfClock *clock;
    map_t *map;
    player_t *player;
    menu_t *menu;
    game_state_t state;
    framebuffer_t *buffer;
    sfTexture *texture;
    sfSprite *sprite;
    weapon_t *weapon;
} wolf_t;

// window.c
sfRenderWindow *create_my_window(int width, int height, sfUint32 style);
void window_fullscreen(sfRenderWindow **window, sfUint32 *style);
// map.c
map_t *load_map(char *filename);
void free_map(map_t *map);
// move.c
player_t *create_player(void);
void move_player(player_t *player, map_t *map, float dt);
// wolf3d.c
int init_wolf(wolf_t *wolf);
void free_wolf(wolf_t *wolf);
// menu.c
menu_t *init_menu(void);
void display_menu(sfRenderWindow *window, menu_t *menu);
void destroy_menu(menu_t *menu);
// drawing.c
void render_wolf(wolf_t *wolf);

#endif
