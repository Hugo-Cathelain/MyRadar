/*
** EPITECH PROJECT, 2023
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** radar
*/
#include "../include/my_radar.h"

static void toggle_rectangle(sfRenderWindow *wdw, sprite_t *air,
    sfEvent *event, sprite_t *tow)
{
    if (event->key.code == sfKeyL) {
        if (air->thick == 2.0) {
            air->thick = 0;
            sfCircleShape_setOutlineThickness(tow->circle, air->thick);
            return sfRectangleShape_setOutlineThickness(air->rec, air->thick);
        }
        if (air->thick == 0) {
            air->thick = 2.0;
            sfCircleShape_setOutlineThickness(tow->circle, air->thick);
            return sfRectangleShape_setOutlineThickness(air->rec, air->thick);
        }
    }
}

static void analyse_event(sfRenderWindow *wdw, all_sprite_t *all, int *disp)
{
    sfEvent event;

    if (sfRenderWindow_pollEvent(wdw, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(wdw);
        if (event.type == sfEvtKeyPressed)
            toggle_rectangle(wdw, all->air, &event, all->tow);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS)
            *disp = *disp == 0;
    }
}

int get_air(char *map)
{
    int count = 0;

    for (int i = 0; map[i]; i++)
        if (map[i] == ' ')
            count++;
    if (count != 6)
        return 1;
    return 0;
}

static int get_tow(char *map)
{
    int count = 0;

    for (int i = 0; map[i]; i++)
        if (map[i] == ' ')
            count++;
    if (count != 3)
        return 1;
    return 0;
}

void draw_tow(sfRenderWindow *wdw, char *map, sprite_t *tow)
{
    char *tmp;
    char *token;
    sfVector2f pos;
    float rad;

    tmp = my_strdup(map);
    token = my_strtok((char *)tmp, " \t");
    token = my_strtok(NULL, " \t");
    pos.x = my_atof(token);
    token = my_strtok(NULL, " \t");
    pos.y = my_atof(token);
    token = my_strtok(NULL, " \t");
    rad = my_atof(token);
    sfCircleShape_setRadius(tow->circle, rad);
    sfSprite_setPosition(tow->sprite, pos);
    pos.x = pos.x - rad + 10;
    pos.y = pos.y - rad + 20;
    sfCircleShape_setPosition(tow->circle, pos);
    sfRenderWindow_drawCircleShape(wdw, tow->circle, NULL);
    sfRenderWindow_drawSprite(wdw, tow->sprite, NULL);
}

void draw_air(sfRenderWindow *wdw, char *map, sprite_t *air)
{
    char *tmp;
    char *token;
    sfVector2f pos;

    tmp = my_strdup(map);
    token = my_strtok((char *)tmp, " \t");
    token = my_strtok(NULL, " \t");
    pos.x = my_atof(token);
    token = my_strtok(NULL, " \t");
    pos.y = my_atof(token);
    token = my_strtok(NULL, " \t");
    sfSprite_setPosition(air->sprite, pos);
    sfRectangleShape_setPosition(air->rec, pos);
    sfRenderWindow_drawRectangleShape(wdw, air->rec, NULL);
    sfRenderWindow_drawSprite(wdw, air->sprite, NULL);
}

void draw(sfRenderWindow *wdw, all_sprite_t *all, char **map)
{
    for (int i = 0; map[i]; i++) {
        if (map[i][0] && map[i][0] == 'T')
            draw_tow(wdw, map[i], all->tow);
        if (map[i][0] && map[i][0] == 'A')
            draw_air(wdw, map[i], all->air);
    }
}

static int invalid_args(char **map)
{
    int err = 0;

    for (int i = 0; map[i]; i++) {
        if (map[i][0] && map[i][0] == 'A')
            err = get_air(map[i]);
        if (map[i][0] && map[i][0] == 'T')
            err = get_tow(map[i]);
        if (map[i][0] && map[i][0] != 'A' && map[i][0] != 'T')
            return 1;
    }
    if (err != 0)
        return 1;
    return 0;
}

int my_radar(char **map)
{
    sfRenderWindow *wdw;
    sfVideoMode vid = {1920, 1080, 60};
    sprite_t *bck = set_background();
    all_sprite_t *all = set_all();
    int disp = 0;
    sfText *txt = set_txt();

    if (invalid_args(map))
        return 84;
    wdw = sfRenderWindow_create(vid, "My_radar", sfClose | sfResize, NULL);
    while (sfRenderWindow_isOpen(wdw)) {
        sfRenderWindow_clear(wdw, sfBlack);
        sfRenderWindow_drawSprite(wdw, bck->sprite, NULL);
        analyse_event(wdw, all, &disp);
        if (disp == 0)
            draw(wdw, all, map);
        sfRenderWindow_drawText(wdw, txt, NULL);
        sfRenderWindow_display(wdw);
    }
    return 0;
}
