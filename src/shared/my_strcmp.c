/*
** EPITECH PROJECT, 2023
** B-PSU-100-LYN-1-1-myls-hugo.cathelain
** File description:
** my_strcmp
*/

static char my_lower(char const c)
{
    if (c >= 'A' && c <= 'Z')
        return (c + 32);
    return c;
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    if (!(s2) || !(s1))
        return 0;
    for (i = 0; (my_lower(s1[i]) == my_lower(s2[i])) && ((s1[i] != '\0') &&
        (s2[i] != '\0')); i++);
    return (my_lower(s1[i]) - my_lower(s2[i]));
}
