/*
** EPITECH PROJECT, 2019
** my_put_nbr
** File description:
** him give one number and write in the console
*/

#include "ia.h"
#include <stdlib.h>

int check_select_ia(int line, char **map)
{
    int next = 0;

    if (line == 0)
        return (1);
    for (int i = 1; map[line][i] != '*'; i++)
        if (map[line][i] == '|')
            next++;
    if (next == 0)
        return (1);
    return (0);
}

void my_ramdom_ia(struct ia *ia, char **map, int nb_line, int max_match)
{
    int nb = 0;

    ia->line = rand()%nb_line + 1;
    while (check_select_ia(ia->line, map) == 1)
        ia->line = rand()%nb_line + 1;
    for (int i = 1; map[ia->line][i] != '*'; i++)
        if (map[ia->line][i] == '|')
            nb++;
    if (nb == 1)
        ia->macht = 1;
    else
        while ((ia->macht = rand()%nb) == 0
                || ia->macht > max_match);
}

void turn_ia(struct ia *ia, char **map, int line, int max_match)
{
    my_ramdom_ia(ia, map, line, max_match);
}
