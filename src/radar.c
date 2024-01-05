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
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyQ)
            all->quad = all->quad == 0;
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

sfVector2f get_pos(char *tmp, char *token, sfVector2f pos)
{
    token = my_strtok(NULL, " \t");
    pos.x = my_atof(token);
    token = my_strtok(NULL, " \t");
    pos.y = my_atof(token);
    return pos;
}

static void draw_tow(sfRenderWindow *wdw, char *map, all_sprite_t *all)
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

int draw_air(sfRenderWindow *wdw, char *map, all_sprite_t *all, float seconds)
{
    char *tmp = my_strdup(map);
    char *token = my_strtok((char *)tmp, " \t");
    sfVector2f pos = get_pos(tmp, token, pos);
    sfVector2f arr = get_pos(tmp, token, arr);
    sfVector2f sped = get_pos(tmp, token, arr);
    float distance = sqrt(pow(arr.x - pos.x, 2) + pow(arr.y - pos.y, 2));

    if (seconds > sped.y) {
        pos.x += (sped.x * (seconds - sped.y)) * (arr.x - pos.x) / distance;
        pos.y += (sped.x * (seconds - sped.y)) * (arr.y - pos.y) / distance;
    }
    if (fabs(pos.x - arr.x) < MARGE && fabs(pos.y - arr.y) < MARGE)
        return 1;
    sfSprite_setPosition(all->air->sprite, pos);
    sfRectangleShape_setPosition(all->air->rec, pos);
    if (!all->shap && seconds > sped.y)
        sfRenderWindow_drawRectangleShape(wdw, all->air->rec, NULL);
    if (!all->disp && seconds > sped.y)
        sfRenderWindow_drawSprite(wdw, all->air->sprite, NULL);
    return 0;
}

void draw_next_air(sfRenderWindow *wdw, all_sprite_t *all, float s,
    char **map)
{
    for (int i = 0; all->pl[i]; i++)
        if (!all->pl[i]->crashed && all->pl[i]->depart <= s) {
            all->pl[i]->crashed += draw_air(wdw, map[all->pl[i]->id], all, s);
            all->av++;
        }
}

static int draw(sfRenderWindow *wdw, all_sprite_t *all, char **map,
    float seconds)
{
    char *txt = malloc(sizeof(char) * 99);
    char *ttt = "time is ";
    char *ttx = " seconds";

    my_itob((int)seconds, txt, 10);
    txt = my_strcat(txt, ttx);
    txt = my_strcat(ttt, txt);
    sfText_setString(all->txt, txt);
    free(txt);
    sfRenderWindow_drawSprite(wdw, all->bck->sprite, NULL);
    all->av = 0;
    for (int i = 0; map[i]; i++)
        if (map[i][0] && map[i][0] == 'T')
            draw_tow(wdw, map[i], all);
    draw_next_air(wdw, all, seconds, map);
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

int my_radar(char **map, struct stat *file)
{
    sfRenderWindow *wdw = set_wdw();
    all_sprite_t *all = set_all(map, file);
    timer_time *timer = set_time();
    sfVector2f pos = {8, 8};
    sfVector2f size = {1916, 1076};
    quadtree_t *quad = set_quad(pos, size);

    while (sfRenderWindow_isOpen(wdw)) {
        timer->tim = sfClock_getElapsedTime(timer->clock);
        timer->sec = timer->tim.microseconds / 1000000.0;
        analyse_event(wdw, all);
        draw(wdw, all, map, timer->sec);
        set_base(quad, timer->sec, all, map);
        draw_quad(quad, all, wdw, timer->sec);
        if (!all->av || test_av(all))
            sfRenderWindow_close(wdw);
        sfRenderWindow_display(wdw);
        sfRenderWindow_clear(wdw, sfBlack);
    }
    return 0;
}
