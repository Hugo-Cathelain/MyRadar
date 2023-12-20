/*
** EPITECH PROJECT, 2023
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** set_sprites
*/
#include "../include/my_radar.h"

sprite_t *set_background(void)
{
    sprite_t *backg = malloc(sizeof(sprite_t));
    sfVector2f pos = {0, 0};
    sfVector2f scale = {0.413, 0.302};

    backg->sprite = sfSprite_create();
    backg->pos = pos;
    backg->texture = sfTexture_createFromFile("map.jpg", NULL);
    backg->scale = scale;
    sfSprite_setTexture(backg->sprite, backg->texture, sfFalse);
    sfSprite_setScale(backg->sprite, scale);
    sfSprite_setPosition(backg->sprite, pos);
    return backg;
}

static sfCircleShape *set_circle(sfVector2f pos)
{
    sfCircleShape *circ = sfCircleShape_create();

    pos.x = pos.x - 40.0;
    pos.y = pos.y - 30.0;
    sfCircleShape_setOutlineColor(circ, sfRed);
    sfCircleShape_setOutlineThickness(circ, 2.0);
    sfCircleShape_setPosition(circ, pos);
    sfCircleShape_setRadius(circ, 50.0);
    sfCircleShape_setFillColor(circ, sfTransparent);
    return circ;
}

static sprite_t *set_tower(void)
{
    sprite_t *tow = malloc(sizeof(sprite_t));
    sfVector2f pos = {320, 240};
    sfVector2f scale = {0.029, 0.034};

    tow->sprite = sfSprite_create();
    tow->pos = pos;
    tow->texture = sfTexture_createFromFile("tower.png", NULL);
    tow->scale = scale;
    tow->circle = set_circle(pos);
    sfSprite_setTexture(tow->sprite, tow->texture, sfFalse);
    sfSprite_setScale(tow->sprite, scale);
    sfSprite_setPosition(tow->sprite, pos);
    return tow;
}

static sfRectangleShape *set_rec(sfVector2f pos)
{
    sfRectangleShape *rec = sfRectangleShape_create();
    sfVector2f size = {20, 20};
    sfVector2f origint = {10, 10};

    sfRectangleShape_setOrigin(rec, origint);
    sfRectangleShape_setFillColor(rec, sfTransparent);
    sfRectangleShape_setSize(rec, size);
    sfRectangleShape_setPosition(rec, pos);
    sfRectangleShape_setOutlineColor(rec, sfYellow);
    sfRectangleShape_setOutlineThickness(rec, 2.0);
    return rec;
}

static sprite_t *set_airplane(void)
{
    sprite_t *airp = malloc(sizeof(sprite_t));
    sfVector2f pos = {90, 90};
    sfVector2f scale = {0.022, 0.022};
    sfVector2f origin = {450, 450};

    airp->sprite = sfSprite_create();
    airp->pos = pos;
    airp->texture = sfTexture_createFromFile("airplane.png", NULL);
    airp->scale = scale;
    airp->rec = set_rec(pos);
    airp->thick = 2.0;
    sfSprite_setOrigin(airp->sprite, origin);
    sfSprite_setTexture(airp->sprite, airp->texture, sfFalse);
    sfSprite_setScale(airp->sprite, scale);
    sfSprite_setPosition(airp->sprite, pos);
    return airp;
}

sfText *set_txt(void)
{
    sfText *txt = sfText_create();
    sfFont* font = sfFont_createFromFile("arial.ttf");
    sfVector2f pos = {1750, 50};

    sfText_setColor(txt, sfWhite);
    sfText_setPosition(txt, pos);
    sfText_setFont(txt, font);
    sfText_setCharacterSize(txt, 25);
    sfText_setString(txt, "time : NULL");
    return txt;
}

all_sprite_t *set_all(void)
{
    all_sprite_t *all = malloc(sizeof(all_sprite_t));

    all->air = set_airplane();
    all->tow = set_tower();
    all->txt = set_txt();
    all->disp = 0;
    all->shap = 0;
    all->av = 0;
    return all;
}

sfRenderWindow *set_wdw(void)
{
    sfRenderWindow *wdw;
    sfVideoMode vid = {1920, 1080, 60};

    wdw = sfRenderWindow_create(vid, "My_radar", sfClose | sfResize, NULL);
    return wdw;
}
