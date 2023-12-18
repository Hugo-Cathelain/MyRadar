/*
** EPITECH PROJECT, 2023
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** my_strcpy
*/
#include "../../include/my_radar.h"

char *my_strcpy(char *dest, const char *src)
{
    char *originalDest = dest;

    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    return originalDest;
}
