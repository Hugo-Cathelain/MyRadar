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
    #include <stdio.h>

typedef struct {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfVector2f scale;
    sfIntRect rect;
    sfRectangleShape *rec;
    float thick;
    sfCircleShape *circle;
    int speed;
    int depart;
} sprite_t;

typedef struct {
    sprite_t *air;
    sprite_t *tow;
} all_sprite_t;

int my_strlen(char const *str);
void my_putstr(char *str);
char *my_strtok(char *str, const char *delimiters);
int my_strcmp(char const *s1, char const *s2);
char *my_strdup(char *str);
char *my_strcpy(char *dest, const char *src);
double my_atof(const char *str);
int my_isdigit(char ch);

int my_radar(char **map);
sprite_t *set_background(void);
sfText *set_txt(void);

#endif /* !MY_RADAR_H_ */
