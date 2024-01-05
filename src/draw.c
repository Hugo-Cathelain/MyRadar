/*
** EPITECH PROJECT, 2024
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** draw
*/
#include "../include/my_radar.h"

int tower_here(sfVector2f pos, char **map)
{
    float dist;
    char *tmp;
    char *token;
    sfVector2f tow;
    float rad;

    for (int i = 0; map[i]; i++) {
        if (map[i][0] == 'T') {
            tmp = my_strdup(map[i]);
            token = my_strtok((char *)tmp, " \t");
            tow = get_pos(tmp, token, tow);
            token = my_strtok(NULL, " \t");
            rad = my_atof(token);
            dist = sqrt(pow(tow.x - pos.x, 2) + pow(tow.y - pos.y, 2));
        }
        if (map[i][0] == 'T' && dist < rad)
            return 0;
    }
    return 1;
}

static sfVector2f speed_multi(plane_t *pl, float sec)
{
    sfVector2f tm = pl->pos;
    float dist = sqrt(pow(pl->arr.x - tm.x, 2) + pow(pl->arr.y - tm.y, 2));

    tm.x += (pl->speed * (sec - pl->depart)) * (pl->arr.x - tm.x) / dist;
    tm.y += (pl->speed * (sec - pl->depart)) * (pl->arr.y - tm.y) / dist;
    return tm;
}

void collion_relay(quadtree_t *quad, all_sprite_t *all, sfVector2i i_j,
    float sec)
{
    float marge = 25;
    sfVector2f arr = speed_multi(quad->planes[i_j.x], sec);
    sfVector2f pos = speed_multi(quad->planes[i_j.y], sec);
    float distance = sqrt(pow(arr.x - pos.x, 2) + pow(arr.y - pos.y, 2));

    if (quad->planes[i_j.x]->crashed || quad->planes[i_j.y]->crashed)
        return;
    if (i_j.x != i_j.y && (tower_here(quad->planes[i_j.x]->pos, all->map) &&
        tower_here(quad->planes[i_j.y]->pos, all->map)) && distance <= marge) {
        quad->planes[i_j.x]->crashed = 1;
        quad->planes[i_j.y]->crashed = 1;
        all->pl[quad->planes[i_j.x]->num]->crashed = 1;
        all->pl[quad->planes[i_j.y]->num]->crashed = 1;
    }
}

void collision(quadtree_t *quad, float seconds, all_sprite_t *all)
{
    sfVector2f pos = {0, 0};
    sfVector2i i_j;

    if (quad->top_left) {
        collision(quad->top_left, seconds, all);
        collision(quad->top_right, seconds, all);
        collision(quad->bot_left, seconds, all);
        collision(quad->bot_right, seconds, all);
    }
    if (!quad->planes)
        return;
    for (int i = 0; i < quadtree_planes_size(quad->planes); i++)
        for (int j = 0; j < quadtree_planes_size(quad->planes); j++) {
            i_j.x = i;
            i_j.y = j;
            collion_relay(quad, all, i_j, seconds);
        }
}

int test_av(all_sprite_t *all)
{
    for (int i = 0; all->pl[i]; i++)
        if (all->pl[i]->crashed == 0)
            return 0;
    return 1;
}

timer_time *set_time(void)
{
    timer_time *timer = malloc(sizeof(timer_time));
    sfTime tim;
    float seconds;

    timer->clock = sfClock_create();
    return timer;
}
