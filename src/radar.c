/*
** EPITECH PROJECT, 2023
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** radar
*/
#include "../include/my_radar.h"

static analyse_event(sfRenderWindow *wdw)
{
    sfEvent event;

    if (sfRenderWindow_pollEvent(wdw, &event))
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(wdw);
}

void draw(sfRenderWindow *wdw, sprite_t *bck, sprite_t *air, sprite_t *tow)
{
    sfRenderWindow_clear(wdw, sfBlack);
    sfRenderWindow_drawSprite(wdw, bck->sprite, NULL);
    sfRenderWindow_drawSprite(wdw, air->sprite, NULL);
    sfRenderWindow_drawRectangleShape(wdw, air->rec, NULL);
    sfRenderWindow_drawSprite(wdw, tow->sprite, NULL);
}

int invalid_args(char **map)
{
    return 0;
}

int my_radar(char **map)
{
    sfRenderWindow *wdw;
    sfVideoMode vid = {1920, 1080, 60};
    sprite_t *bck = set_background();
    sprite_t *air = set_airplane();
    sprite_t *tow = set_tower();

    if (invalid_args(map))
        return 84;
    wdw = sfRenderWindow_create(vid, "My_radar", sfClose | sfResize, NULL);
    while (sfRenderWindow_isOpen(wdw)) {
        sfRenderWindow_display(wdw);
        analyse_event(wdw);
        draw(wdw, bck, air, tow);
    }
    return 0;
}
