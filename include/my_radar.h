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
    #include <stdlib.h>
    #include <math.h>

    #define QT_NODE_CAPACITY (4)
    #define MARGE (1)

typedef struct {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfVector2f scale;
    sfIntRect rect;
    sfRectangleShape *rec;
    sfCircleShape *circle;
    int speed;
    int depart;
} sprite_t;

typedef struct {
    sfVector2f pos;
    sfVector2f arr;
    int speed;
    int depart;
    int crashed;
    int id;
    int num;
} plane_t;

typedef struct {
    sprite_t *air;
    sprite_t *tow;
    sprite_t *bck;
    sfText *txt;
    int shap;
    int disp;
    int quad;
    int av;
    plane_t **pl;
    int count_plan;
} all_sprite_t;

typedef struct {
    sfClock * clock;
    sfTime tim;
    float sec;
} timer_time;

typedef struct {
    sfVector2f pos;
    sfVector2f size;
} pos_size_t;

typedef struct quad {
    struct quad *top_left;
    struct quad *top_right;
    struct quad *bot_left;
    struct quad *bot_right;
    pos_size_t *boundry;
    plane_t **planes;
} quadtree_t;

int my_strlen(char const *str);
void my_putstr(char *str);
char *my_strtok(char *str, const char *delimiters);
int my_strcmp(char const *s1, char const *s2);
char *my_strdup(char *str);
char *my_strcpy(char *dest, const char *src);
double my_atof(const char *str);
int my_isdigit(char ch);

int my_radar(char **map, struct stat *file);
int invalid_args(char **map);
all_sprite_t *set_all(char **map, struct stat *file);
sprite_t *set_background(void);
sfRenderWindow *set_wdw(void);
sfVector2f get_pos(char *tmp, char *token, sfVector2f pos);
void set_base(struct quad *quad, float seconds, all_sprite_t *all, char **map);
quadtree_t *set_quad(sfVector2f pos, sfVector2f size);
void collision(quadtree_t *quad, float seconds, all_sprite_t *all, char **map);
plane_t *get_plane(char *tmp, char *token, plane_t *plane);
size_t quadtree_planes_size(plane_t *planes[]);
int test_av(all_sprite_t *all);
timer_time *set_time(void);

#endif /* !MY_RADAR_H_ */
