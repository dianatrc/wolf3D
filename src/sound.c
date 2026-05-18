/*
** EPITECH PROJECT, 2026
** WOLFENSTEIN3D
** File description:
** Main sound functions
*/

#include "../include/wolf3d.h"

static int load_audios(sound_t *sounds)
{
    sounds->music = sfMusic_createFromFile("utils/music.ogg");
    sounds->shoot_buf = sfSoundBuffer_createFromFile("utils/gunshot.wav");
    sounds->click_buf = sfSoundBuffer_createFromFile("utils/click_sound.wav");
    sounds->save_buf = sfSoundBuffer_createFromFile("utils/save_sound.wav");
    if (!sounds->music || !sounds->shoot_buf || !sounds->click_buf ||
        !sounds->save_buf)
        return 84;
    return 0;
}

sound_t *init_sounds(void)
{
    sound_t *sounds = malloc(sizeof(sound_t));

    if (!sounds)
        return NULL;
    sounds->music = NULL;
    sounds->shoot = NULL;
    sounds->click = NULL;
    sounds->save = NULL;
    if (load_audios(sounds) == 84) {
        free_sounds(sounds);
        return NULL;
    }
    sounds->shoot = sfSound_create();
    sounds->click = sfSound_create();
    sounds->save = sfSound_create();
    if (!sounds->shoot || !sounds->click || !sounds->save) {
        free_sounds(sounds);
        return NULL;
    }
    sfSound_setBuffer(sounds->shoot, sounds->shoot_buf);
    sfSound_setBuffer(sounds->click, sounds->click_buf);
    sfSound_setBuffer(sounds->save, sounds->save_buf);
    sfMusic_setLoop(sounds->music, sfTrue);
    if (sfMusic_getStatus(sounds->music) != sfPlaying)
        sfMusic_play(sounds->music);
    return sounds;
}

void update_volume(wolf_t *wolf, float offset)
{
    if (!wolf || !wolf->sounds)
        return;
    wolf->menu->volume += offset;
    if (wolf->menu->volume < 0)
        wolf->menu->volume = 0;
    if (wolf->menu->volume > 100)
        wolf->menu->volume = 100;
    if (wolf->sounds->music)
        sfMusic_setVolume(wolf->sounds->music, wolf->menu->volume);
    if (wolf->sounds->click)
        sfSound_setVolume(wolf->sounds->click, wolf->menu->volume);
    if (wolf->sounds->save)
        sfSound_setVolume(wolf->sounds->save, wolf->menu->volume);
    if (wolf->sounds->shoot)
        sfSound_setVolume(wolf->sounds->shoot, wolf->menu->volume);
}

static void free_sounds_helper(sound_t *sounds)
{
    if (sounds->shoot_buf)
        sfSoundBuffer_destroy(sounds->shoot_buf);
    if (sounds->click_buf)
        sfSoundBuffer_destroy(sounds->click_buf);
    if (sounds->save_buf)
        sfSoundBuffer_destroy(sounds->save_buf);
    free(sounds);
}

void free_sounds(sound_t *sounds)
{
    if (!sounds)
        return;
    if (sounds->music) {
        sfMusic_stop(sounds->music);
        sfMusic_destroy(sounds->music);
    }
    if (sounds->shoot) {
        sfSound_stop(sounds->shoot);
        sfSound_destroy(sounds->shoot);
    }
    if (sounds->click) {
        sfSound_stop(sounds->click);
        sfSound_destroy(sounds->click);
    }
    if (sounds->save) {
        sfSound_stop(sounds->save);
        sfSound_destroy(sounds->save);
    }
    free_sounds_helper(sounds);
}
