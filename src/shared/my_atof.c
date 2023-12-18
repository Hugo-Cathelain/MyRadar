/*
** EPITECH PROJECT, 2023
** libmy
** File description:
** my_atof
*/
#include "../../include/my_radar.h"

static const char *skip_white_space(const char *str, int *sign)
{
    while (*str == ' ' || *str == '\t')
        str++;
    if (*str == '-') {
        *sign = -1;
        str++;
    } else if (*str == '+')
        str++;
    return (str);
}

double my_atof(const char *str)
{
    double result = 0.0;
    double fraction = 0.0;
    double divider = 10.0;
    int sign = 1;

    str = skip_white_space(str, &sign);
    while (my_isdigit(*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }
    if (*str == '.') {
        str++;
        while (my_isdigit(*str)) {
            fraction += (*str - '0') / divider;
            divider *= 10;
            str++;
        }
        result += fraction;
    }
    return (result * sign);
}
