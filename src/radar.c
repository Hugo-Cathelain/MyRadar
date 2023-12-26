/*
** EPITECH PROJECT, 2023
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** radar
*/
#include "../include/my_radar.h"

static void analyse_event(sfRenderWindow *wdw, all_sprite_t *all)
{
    sfEvent event;

    if (sfRenderWindow_pollEvent(wdw, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(wdw);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyL)
            all->shap = all->shap == 0;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS)
            all->disp = all->disp == 0;
    }
}

static int get_air(char *map)
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

static sfVector2f get_pos(char *tmp, char *token, sfVector2f pos)
{
    token = my_strtok(NULL, " \t");
    pos.x = my_atof(token);
    token = my_strtok(NULL, " \t");
    pos.y = my_atof(token);
    return pos;
}

void draw_tow(sfRenderWindow *wdw, char *map, all_sprite_t *all, float seconds)
{
    char *tmp = my_strdup(map);
    char *token = my_strtok((char *)tmp, " \t");
    sfVector2f pos = get_pos(tmp, token, pos);
    float rad;

    token = my_strtok(NULL, " \t");
    rad = my_atof(token);
    sfCircleShape_setRadius(all->tow->circle, rad);
    sfSprite_setPosition(all->tow->sprite, pos);
    pos.x = pos.x - rad + 10;
    pos.y = pos.y - rad + 20;
    sfCircleShape_setPosition(all->tow->circle, pos);
    if (!all->shap)
        sfRenderWindow_drawCircleShape(wdw, all->tow->circle, NULL);
    if (!all->disp)
    sfRenderWindow_drawSprite(wdw, all->tow->sprite, NULL);
}

void draw_air(sfRenderWindow *wdw, char *map, all_sprite_t *all, float seconds)
{
    char *tmp = my_strdup(map);
    char *token = my_strtok((char *)tmp, " \t");
    sfVector2f pos = get_pos(tmp, token, pos);
    sfVector2f arr = get_pos(tmp, token, arr);
    sfVector2f sped = get_pos(tmp, token, arr);
    float marge = 1;
    float distance = sqrt(pow(arr.x - pos.x, 2) + pow(arr.y - pos.y, 2));

    pos.x += (sped.x * seconds - sped.y) * (arr.x - pos.x) / distance;
    pos.y += (sped.x * seconds - sped.y) * (arr.y - pos.y) / distance;
    if (fabs(pos.x - arr.x) < marge && fabs(pos.y - arr.y) < marge) {
        map[0] = 'O';
        return;
    }
    sfSprite_setPosition(all->air->sprite, pos);
    sfRectangleShape_setPosition(all->air->rec, pos);
    if (!all->shap)
        sfRenderWindow_drawRectangleShape(wdw, all->air->rec, NULL);
    if (!all->disp)
        sfRenderWindow_drawSprite(wdw, all->air->sprite, NULL);
}

int draw(sfRenderWindow *wdw, all_sprite_t *all, char **map, float seconds)
{
    all->av = 0;
    for (int i = 0; map[i]; i++) {
        if (map[i][0] && map[i][0] == 'T')
            draw_tow(wdw, map[i], all, seconds);
        if (map[i][0] && map[i][0] == 'A') {
            draw_air(wdw, map[i], all, seconds);
            all->av++;
        }
    }
    sfRenderWindow_drawText(wdw, all->txt, NULL);
    return 0;
}

int invalid_args(char **map)
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
    sfRenderWindow *wdw = set_wdw();
    sprite_t *bck = set_background();
    all_sprite_t *all = set_all();
    sfClock *clock = sfClock_create();
    sfTime tim;
    float seconds;

    while (sfRenderWindow_isOpen(wdw)) {
        tim = sfClock_getElapsedTime(clock);
        seconds = tim.microseconds / 100000.0;
        sfRenderWindow_drawSprite(wdw, bck->sprite, NULL);
        analyse_event(wdw, all);
        draw(wdw, all, map, seconds);
        if (!all->av)
            sfRenderWindow_close(wdw);
        sfRenderWindow_display(wdw);
        sfRenderWindow_clear(wdw, sfBlack);
    }
    return 0;
}
