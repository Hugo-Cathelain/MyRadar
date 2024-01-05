/*
** EPITECH PROJECT, 2023
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** quadtree
*/

#include "../include/my_radar.h"

quadtree_t *set_quad(sfVector2f pos, sfVector2f size)
{
    quadtree_t *quad = malloc(sizeof(quadtree_t));

    quad->boundry = malloc(sizeof(pos_size_t));
    quad->boundry->pos = pos;
    quad->boundry->size = size;
    quad->top_left = NULL;
    quad->top_right = NULL;
    quad->bot_left = NULL;
    quad->bot_right = NULL;
    quad->planes = (plane_t **)malloc(sizeof(plane_t *) * QT_NODE_CAPACITY);
    for (size_t i = 0; i < QT_NODE_CAPACITY; i++)
        quad->planes[i] = NULL;
    return quad;
}

static quadtree_t *subdivide(struct quad *quad)
{
    sfVector2f nw_size;
    sfVector2f nw_posTR;
    sfVector2f nw_posBL;
    sfVector2f nw_posBR;

    nw_size.x = quad->boundry->size.x / 2.0;
    nw_size.y = quad->boundry->size.y / 2.0;
    nw_posTR.x = quad->boundry->pos.x + nw_size.x;
    nw_posTR.y = quad->boundry->pos.y;
    nw_posBL.x = quad->boundry->pos.x;
    nw_posBL.y = quad->boundry->pos.y + nw_size.y;
    nw_posBR.x = quad->boundry->pos.x + nw_size.x;
    nw_posBR.y = quad->boundry->pos.y + nw_size.y;
    quad->top_left = set_quad(quad->boundry->pos, nw_size);
    quad->top_right = set_quad(nw_posTR, nw_size);
    quad->bot_left = set_quad(nw_posBL, nw_size);
    quad->bot_right = set_quad(nw_posBR, nw_size);
    return quad;
}

static int quad_cotains_plane(pos_size_t *boundry, plane_t *plane,
    float seconds)
{
    float travel = (plane->speed * (seconds - plane->depart));
    sfVector2f tmp = plane->pos;
    sfVector2f tm = plane->arr;
    float distance = sqrt(pow(tm.x - tmp.x, 2) + pow(tm.y - tmp.y, 2));

    tmp.x += travel * (plane->arr.x - plane->pos.x) / distance;
    tmp.y += travel * (plane->arr.y - plane->pos.y) / distance;
    if (tmp.x < boundry->pos.x ||
        tmp.x > boundry->size.x + boundry->pos.x)
        return 1;
    if (tmp.y < boundry->pos.y ||
        tmp.y > boundry->size.y + boundry->pos.y)
        return 1;
    return 0;
}

size_t quadtree_planes_size(plane_t *planes[])
{
    size_t i;

    for (i = 0; i < QT_NODE_CAPACITY; i++)
        if (planes[i] == NULL)
            return i;
    return i;
}

static int quadtree_insert(struct quad *root, plane_t *plane, float seconds)
{
    size_t planes_size = quadtree_planes_size(root->planes);

    if (quad_cotains_plane(root->boundry, plane, seconds))
        return 0;
    if (planes_size < QT_NODE_CAPACITY && root->top_left == NULL) {
        root->planes[planes_size] = plane;
        return 1;
    }
    if (root->top_left == NULL)
        subdivide(root);
    if (quadtree_insert(root->top_left, plane, seconds))
        return 1;
    if (quadtree_insert(root->top_right, plane, seconds))
        return 1;
    if (quadtree_insert(root->bot_left, plane, seconds))
        return 1;
    if (quadtree_insert(root->bot_right, plane, seconds))
        return 1;
    return 0;
}

plane_t *get_plane(char *tmp, char *token, plane_t *plane)
{
    sfVector2f pos = get_pos(tmp, token, pos);
    sfVector2f arr = get_pos(tmp, token, arr);
    sfVector2f sped = get_pos(tmp, token, sped);

    plane->pos = pos;
    plane->arr = arr;
    plane->speed = sped.x;
    plane->depart = sped.y;
    plane->crashed = 0;
    return plane;
}

static void destroy_quad(quadtree_t *quad)
{
    if (quad->top_left) {
        destroy_quad(quad->top_left);
        destroy_quad(quad->top_right);
        destroy_quad(quad->bot_left);
        destroy_quad(quad->bot_right);
    }
    if (quad->planes)
        for (int i = 0; i < quadtree_planes_size(quad->planes); i++)
            quad->planes[i] = NULL;
    quad->top_left = NULL;
    quad->top_right = NULL;
    quad->bot_left = NULL;
    quad->bot_right = NULL;
}

void set_base(struct quad *quad, float seconds, all_sprite_t *all, char **map)
{
    destroy_quad(quad);
    for (int i = 0; all->pl[i]; i++)
        if (all->pl[i]->depart <= seconds && !all->pl[i]->crashed)
            quadtree_insert(quad, all->pl[i], seconds);
    collision(quad, seconds, all, map);
}

static void draw_plane(plane_t *plane, sfRenderWindow *wdw, all_sprite_t *all,
    float seconds)
{
    plane_t *tm = plane;
    sfVector2f pos = tm->pos;
    float marge = 0.1;
    float dist = sqrt(pow(tm->arr.x - pos.x, 2) + pow(tm->arr.y - pos.y, 2));
    float trav = (tm->speed * (seconds - tm->depart));

    if (seconds > tm->depart && !plane->crashed) {
        plane->pos.x += trav * (tm->arr.x - tm->pos.x) / dist;
        plane->pos.y += trav * (tm->arr.y - tm->pos.y) / dist;
        all->pl[plane->num]->pos = plane->pos;
    }
    if (fabs(tm->pos.x - tm->arr.x) < marge &&
        fabs(tm->pos.y - tm->arr.y) < marge) {
        plane->crashed = 1;
        all->pl[plane->num]->crashed = 1;
    }
}

void draw_quad(quadtree_t *quad, all_sprite_t *all, sfRenderWindow *wdw,
    float seconds)
{
    sfVector2f size = {20, 20};

    if (quad->top_left) {
        draw_quad(quad->top_left, all, wdw, seconds);
        draw_quad(quad->top_right, all, wdw, seconds);
        draw_quad(quad->bot_left, all, wdw, seconds);
        draw_quad(quad->bot_right, all, wdw, seconds);
    }
    if (quad->planes)
        for (int i = 0; i < quadtree_planes_size(quad->planes); i++)
            draw_plane(quad->planes[i], wdw, all, seconds);
    if (all->quad) {
        sfRectangleShape_setPosition(all->air->rec, quad->boundry->pos);
        sfRectangleShape_setSize(all->air->rec, quad->boundry->size);
        sfRenderWindow_drawRectangleShape(wdw, all->air->rec, NULL);
        sfRectangleShape_setSize(all->air->rec, size);
    }
}
