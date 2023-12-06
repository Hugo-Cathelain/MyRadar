/*
** EPITECH PROJECT, 2023
** B-CPE-110-LYN-1-1-settingup-hugo.cathelain
** File description:
** my_strlen
*/

int my_strlen(char const *str)
{
    int count = 0;

    while (*str != '\0') {
        str++;
        count++;
    }
    return count;
}
