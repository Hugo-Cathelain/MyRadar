/*
** EPITECH PROJECT, 2023
** B-CPE-110-LYN-1-1-organized-hugo.cathelain
** File description:
** my_strdup
*/
#include "../../include/my_radar.h"

char *my_strdup(char *str)
{
    char *res = malloc(my_strlen(str) + 1);
    int i;

    for (i = 0; str[i] && str[i] != '\n'; i++)
        res[i] = str[i];
    res[i] = '\0';
    return res;
}
