/*
** EPITECH PROJECT, 2024
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** my_itob
*/
#include "../../include/my_radar.h"

char *my_strcat(char *str1, char *str2)
{
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);
    char *res = malloc(sizeof(char) * len1 + len2 + 1);
    int i = 0;

    for (i = 0; i < len1 + len2; i++) {
        if (i < len1)
            res[i] = str1[i];
        if (i >= len1)
            res[i] = str2[i - len1];
    }
    res[i] = '\0';
    return res;
}

void my_reverse_str(char *buffer, size_t len)
{
    size_t mid;
    char c;

    if (!buffer)
        return;
    mid = len / 2;
    for (size_t i = 0; i < mid; i++) {
        c = buffer[i];
        buffer[i] = buffer[len - i - 1];
        buffer[len - i - 1] = c;
    }
}

static void my_itob_relay(ssize_t nbr, int base, char *buffer, size_t len)
{
    ssize_t sign = nbr;
    size_t tmp_num;

    if (nbr < 0 && (base == DEC || base == HEX)) {
        sign = -nbr;
        tmp_num = (size_t)sign;
        buffer[len] = '-';
        len++;
    }
    buffer[len] = '\0';
    my_reverse_str(buffer, len);
}

static char buffer_plus(char digit)
{
    if (digit < 10)
        return (digit + '0');
    else
        return (digit - 10 + 'a');
}

void my_itob(ssize_t nbr, char *buffer, int base)
{
    size_t len = 0;
    size_t tmp_num = (nbr < 0) ? -nbr : nbr;
    char digit;

    if (nbr == LONG_MIN)
        tmp_num = (size_t)LONG_MAX + 1;
    if (nbr == SHRT_MIN)
        tmp_num = (size_t)SHRT_MAX + 1;
    if (base != BIN && base != OCT && base != DEC && base != HEX)
        return;
    if (tmp_num == 0) {
        buffer[len] = '0';
        len++;
    } else
        for (len = len; tmp_num > 0; len++) {
            digit = (char)(tmp_num % base);
            buffer[len] = buffer_plus(digit);
            tmp_num /= base;
        }
    my_itob_relay(nbr, base, buffer, len);
}
