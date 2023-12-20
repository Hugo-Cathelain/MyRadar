/*
** EPITECH PROJECT, 2023
** B-MUL-100-LYN-1-1-myradar-hugo.cathelain
** File description:
** main
*/
#include "../include/my_radar.h"

int print_usage(void)
{
    my_putstr("Air traffic simulation panel\n\n");
    my_putstr("USAGE\n    ./my_radar [OPTIONS] path_to_script\n    path_to_s");
    my_putstr("cript   The path to the script file.\n\nOPTION\n    -h    pri");
    my_putstr("nt the usage and quit.\n\nUSER INTERACTIONS\n    \'L\'    ena");
    my_putstr("ble/disable hitboxes and areas.\n    \'S\'    enable/disable ");
    my_putstr("sprites.\n");
    return 0;
}

int rows(char *buffer)
{
    int count = 0;

    for (int i = 0; buffer[i]; i++)
        if (buffer[i] == '\n')
            count++;
    return count;
}

char **get_map(char *buffer)
{
    char **map = malloc(sizeof(char) * 99);
    int i = 0;
    int count = rows(buffer);
    char *token = my_strtok((char *)buffer, "\n");

    for (i = 0; token != NULL; i++) {
        map[i] = malloc(sizeof(char) * (my_strlen(token) + 1));
        my_strcpy(map[i], token);
        map[i][my_strlen(token)] = '\0';
        token = my_strtok(NULL, "\n");
    }
    map[i] = 0;
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
    buffer[file.st_size] = '\0';
    map = get_map(buffer);
    if (invalid_args(map))
        return 84;
    return my_radar(map);
}

int main(int ac, char **av)
{
    if (ac == 2)
        return try_h_flag(av[1]);
    return 84;
}
