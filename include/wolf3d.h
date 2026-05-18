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
    sfVector2f pos;
    sfTexture *texture;
    int health;
    float dist;
} enemy_t;

typedef struct {
    int width;
    int height;
    sfUint8 *pixels;
    float *d_buffer;
} framebuffer_t;

typedef enum {
    MENU,
    GAME,
    SETTINGS
} game_state_t;

typedef struct {
    sfFont *font;
    sfText *title;
    sfText *play_button;
    sfText *save_button;
    sfText *load_button;
    sfText *settings;
    sfText *exit_button;
    sfText *g_to_menu;
    sfSprite *sprite;
    sfTexture *texture;
    sfText *vol_up;
    sfText *vol_down;
    sfText *s_to_menu;
    float volume;
} menu_t;

typedef struct {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f rest_pos;
} weapon_t;

typedef struct {
    sfMusic *music;
    sfSound *shoot;
    sfSoundBuffer *shoot_buf;
    sfSound *click;
    sfSoundBuffer *click_buf;
    sfSound *save;
    sfSoundBuffer *save_buf;
} sound_t;

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
    int flash_on;
    sound_t *sounds;
    enemy_t *enemies;
    int enemy_count;
} wolf_t;

// window.c
sfRenderWindow *create_my_window(int width, int height, sfUint32 style);
void window_fullscreen(sfRenderWindow **window, sfUint32 *style);
// map.c
map_t *load_map(char *filename);
void free_map(map_t *map);
// move.c
player_t *create_player(void);
int is_wall(map_t *map, float x, float y);
void move_player(player_t *player, map_t *map, float dt);
// wolf3d.c
int init_wolf(wolf_t *wolf);
void free_wolf(wolf_t *wolf);
// menu.c
menu_t *init_menu(void);
void display_menu(sfRenderWindow *window, menu_t *menu);
void display_settings(sfRenderWindow *window, menu_t *menu);
void destroy_menu(menu_t *menu);
// drawing.c
void put_pixel(framebuffer_t *buffer, sfColor *color, int x, int y);
void render_wolf(wolf_t *wolf);
// save.c
int save_game(wolf_t *wolf, char *filepath);
int load_save(wolf_t *wolf, char *filepath);
// sound.c
sound_t *init_sounds(void);
void update_volume(wolf_t *wolf, float offset);
void free_sounds(sound_t *sounds);
// enemy.c
void draw_enemies(wolf_t *wolf);
void sort_enemies(wolf_t *wolf);
void update_enemies(wolf_t *wolf, float dt);
// weapon.c
weapon_t *init_weapon(void);
void draw_weapon(sfRenderWindow *window, weapon_t *weapon);
void destroy_weapon(weapon_t *weapon);

#endif
