/*
** EPITECH PROJECT, 2023
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** my_strtok
*/
#include "../../include/my_radar.h"

int is_delimiter(char c, char *delimiters)
{
    while (*delimiters != '\0') {
        if (*delimiters == c)
            return 1;
        delimiters++;
    }
    return 0;
}

char *my_strtok(char *str, const char *delimiters)
{
    static char *lastToken = NULL;
    char *token;

    if (str == NULL)
        str = lastToken;
    while (*str != '\0' && is_delimiter(*str, delimiters))
        str++;
    if (*str == '\0')
        return NULL;
    token = str;
    while (*str != '\0' && !is_delimiter(*str, delimiters))
        str++;
    if (*str == '\0')
        lastToken = NULL;
    else {
        *str = '\0';
        lastToken = str + 1;
    }
    return token;
}
