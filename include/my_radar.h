/*
** EPITECH PROJECT, 2023
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** my_radar
*/

#ifndef MY_RADAR_H_
    #define MY_RADAR_H_

    #include <SFML/Audio.h>
    #include <SFML/Config.h>
    #include <SFML/GPUPreference.h>
    #include <SFML/Graphics.h>
    #include <SFML/Network.h>
    #include <SFML/OpenGL.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <SFML/Graphics/RenderWindow.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>

typedef struct {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfVector2f scale;
    sfIntRect rect;
    sfRectangleShape *rec;
} sprite_t;

int my_strlen(char const *str);
void my_putstr(char *str);

sprite_t *set_background(void);

#endif /* !MY_RADAR_H_ */
