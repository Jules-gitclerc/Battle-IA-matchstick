/*
** EPITECH PROJECT, 2019
** my_put_nbr
** File description:
** him give one number and write in the console
*/

#include "matchstick.h"
#include "my.h"
#include <stdlib.h>

void count_stick(struct map *map, struct info_map *info)
{
    int nb = 0;

    for (int i = 0; i < info->nb_line + 2; i++)
        for (int o = 0; o < info->nb_colum; o++)
            if (map->map[i][o] == '|')
                nb++;
    if (nb == 0)
        info->indic_wog = 1;
    else
        info->indic_wog = 0;
}

int check_input_col_bis(int nb_col, char **map, int line, int nb_macht_p)
{
    int nb_col_p = 0;

    if (nb_col == 0) {
        my_printf("Error: this line is out of range\n");
        return (-1);
    }
    for (int i = 1; map[line][i] != '*'; i++)
        if (map[line][i] == '|')
            nb_col_p++;
    if (nb_col > nb_col_p) {
        my_printf("Error: not enough matches on this line\n");
        return (-1);
    }
    if (nb_col > nb_macht_p) {
        my_printf("Error: you cannot remove more than ");
        my_printf("%i matches per turn\n", nb_macht_p);
        return (-1);
    }
}

int check_input_col(char *input, char **map, int line, int nb_macht_p)
{
    int nb_col = 0;

    for (int i = 0; input[i] != '\n'; i++)
        if (!(input[i] >= '0' && input[i] <= '9')) {
            my_printf("Error: invalid input (positive number expected)\n");
            return (-1);
        }
    nb_col = recup_info_input(input);
    if (check_input_col_bis(nb_col, map, line, nb_macht_p) == -1)
        return (-1);
    return (nb_col);
}

int input_line_bis(int nb_line, char **map, int nb_line_max, int nb_macth_p)
{
    if (nb_line > nb_line_max) {
        my_printf("Error: this line is out of range\n");
        return (-1);
    } else if (nb_line == 0) {
        my_printf("Error: this line is out of range\n");
        return (-1);
    }
    for (int i = 1; map[nb_line][i] != '*'; i++)
        if (map[nb_line][i] == '|')
            nb_macth_p++;
    if (nb_macth_p <= 0) {
        my_printf("Error: not enough matches on this line\n");
        return (-1);
    }
    return (0);
}

int check_input_line(char *input, char **map, int nb_line_max)
{
    int nb_line = 0;
    int nb_macth_p = 0;

    for (int i = 0; input[i] != '\n'; i++)
        if (!(input[i] >= '0' && input[i] <= '9')) {
            my_printf("Error: invalid input (positive number expected)\n");
            return (-1);
        }
    nb_line = recup_info_input(input);
    if (input_line_bis(nb_line, map, nb_line_max, nb_macth_p) == -1)
        return (-1);
    return (nb_line);
}
