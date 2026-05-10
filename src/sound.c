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
    if (load_audios(sounds) == 84) {
        free_sounds(sounds);
        return NULL;
    }
    sounds->shoot = sfSound_create();
    sounds->click = sfSound_create();
    sounds->save = sfSound_create();
    sfSound_setBuffer(sounds->shoot, sounds->shoot_buf);
    sfSound_setBuffer(sounds->click, sounds->click_buf);
    sfSound_setBuffer(sounds->save, sounds->save_buf);
    sfMusic_setLoop(sounds->music, sfTrue);
    sfMusic_play(sounds->music);
    return sounds;
}

void update_volume(wolf_t *wolf, float offset)
{
    wolf->menu->volume += offset;
    if (wolf->menu->volume < 0)
        wolf->menu->volume = 0;
    if (wolf->menu->volume > 100)
        wolf->menu->volume = 100;
    sfMusic_setVolume(wolf->sounds->music, wolf->menu->volume);
    sfSound_setVolume(wolf->sounds->click, wolf->menu->volume);
    sfSound_setVolume(wolf->sounds->save, wolf->menu->volume);
    sfSound_setVolume(wolf->sounds->shoot, wolf->menu->volume);
}

void free_sounds(sound_t *sounds)
{
    if (!sounds)
        return;
    sfMusic_stop(sounds->music);
    sfSound_stop(sounds->shoot);
    sfSound_stop(sounds->click);
    sfSound_stop(sounds->save);
    sfMusic_destroy(sounds->music);
    sfSound_destroy(sounds->shoot);
    sfSound_destroy(sounds->click);
    sfSound_destroy(sounds->save);
    sfSoundBuffer_destroy(sounds->shoot_buf);
    sfSoundBuffer_destroy(sounds->click_buf);
    sfSoundBuffer_destroy(sounds->save_buf);
    free(sounds);
}
