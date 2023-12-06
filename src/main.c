/*
** EPITECH PROJECT, 2023
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** main
*/
#include "../include/my_radar.h"

int print_usage(void)
{
    my_putstr("USAGE\n    ./my_radar\n\nDESCRIPTION\n");
    my_putstr("");
    my_putstr("");
    my_putstr("");
    my_putstr("");
    my_putstr("");
    return 0;
}

char **get_map(char *buffer)
{
    char **map;
    int i = 0;
    int j = 0;
    int k = 0;

    map = (char **)malloc(sizeof(char *) * my_strlen(buffer) + 2);
    map[k] = (char *)malloc(sizeof(char) * my_strlen(buffer) + 1);
    for (i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n') {
            i++;
            k++;
            map[k] = (char *)malloc(sizeof(char) * my_strlen(buffer) + 1);
            j = 0;
        }
        map[k][j] = buffer[i];
        j++;
    }
    k++;
    map[k] = 0;
    return map;
}

int try_h_flag(char *av)
{
    struct stat file;
    int fileopen;
    char *buffer;
    char **map;

    if (av[0] == '-' && av[1] == 'h' && my_strlen(av) == 2)
        return print_usage();
    fileopen = open(av, O_RDONLY);
    if (fileopen == -1)
        return 84;
    stat(av, &file);
    buffer = malloc(file.st_size);
    read(fileopen, buffer, file.st_size);
    map = get_map(buffer);
    return my_radar(map);
}

int main(int ac, char **av)
{
    if (ac == 2)
        return try_h_flag(av[1]);
    return 84;
}
