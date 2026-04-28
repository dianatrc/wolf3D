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

// window.c
sfRenderWindow *create_my_window(int width, int height, sfUint32 style);
void window_fullscreen(sfRenderWindow **window, sfUint32 *style);

#endif
