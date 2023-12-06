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

sprite_t *set_tower(void)
{
    sprite_t *tow = malloc(sizeof(sprite_t));
    sfVector2f pos = {400, 600};
    sfVector2f scale = {0.029, 0.034};

    tow->sprite = sfSprite_create();
    tow->pos = pos;
    tow->texture = sfTexture_createFromFile("tower.png", NULL);
    tow->scale = scale;
    sfSprite_setTexture(tow->sprite, tow->texture, sfFalse);
    sfSprite_setScale(tow->sprite, scale);
    sfSprite_setPosition(tow->sprite, pos);
    return tow;
}

sfRectangleShape *set_rec(sfVector2f pos)
{
    sfRectangleShape *rec = sfRectangleShape_create();
    sfVector2f size = {20, 20};

    sfRectangleShape_setFillColor(rec, sfTransparent);
    sfRectangleShape_setSize(rec, size);
    sfRectangleShape_setPosition(rec, pos);
    sfRectangleShape_setOutlineColor(rec, sfYellow);
    sfRectangleShape_setOutlineThickness(rec, 2.0);
    return rec;
}

sprite_t *set_airplane(void)
{
    sprite_t *airp = malloc(sizeof(sprite_t));
    sfVector2f pos = {800, 500};
    sfVector2f scale = {0.022, 0.022};

    airp->sprite = sfSprite_create();
    airp->pos = pos;
    airp->texture = sfTexture_createFromFile("airplane.png", NULL);
    airp->scale = scale;
    airp->rec = set_rec(pos);
    sfSprite_setTexture(airp->sprite, airp->texture, sfFalse);
    sfSprite_setScale(airp->sprite, scale);
    sfSprite_setPosition(airp->sprite, pos);
    return airp;
}
