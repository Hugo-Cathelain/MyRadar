/*
** EPITECH PROJECT, 2023
** lib
** File description:
** my_atoi
*/

#include "../../include/my_radar.h"

int my_atoi(char *nptr)
{
    int nbr = 0;

    while (my_isdigit(*nptr)) {
        nbr = nbr * 10 + (*nptr - '0');
        nptr++;
    }
    return (nbr);
}
