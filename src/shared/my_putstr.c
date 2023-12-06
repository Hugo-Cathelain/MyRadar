/*
** EPITECH PROJECT, 2023
** lib
** File description:
** my_putstr
*/

#include "../../include/my_radar.h"

void my_putstr(char *str)
{
    int len = my_strlen(str);

    write(1, str, len);
}
