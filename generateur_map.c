/*
** EPITECH PROJECT, 2019
** workshop_tournoi_ia
** File description:
** generateur_map.c
*/

#include <stdlib.h>

int nb_col_in_line(int line)
{
    int nb_col = 1;

    for (int i = 0; i < line; i++)
        nb_col += 2;
    return (nb_col);
}

char *fil_line(char *str, int locat, int re, int nb_col)
{
    int nb = 0;

    for (int i = 1; i < nb_col - 1; i++) {
        if (locat + 1 == i && nb < re) {
            str[i] = '|';
            nb++;
            locat++;
        } else
            str[i] = ' ';
    }
    return (str);
}

char **fil_tab(int line, int nb_col, char **map)
{
    int number_space = (nb_col - 2) / 2;
    int nb = 1;

    for (int i = 0; i < line + 2; i++) {
        for (int o = 1; o < nb_col - 1; o++) {
            if (i == 0 || i == line + 1)
                map[i][o] = '*';
            else {
                map[i] = fil_line(map[i], number_space, nb, nb_col);
                o = nb_col;
                nb += 2;
                number_space--;
            }
        }
    }
    return (map);
}

char **print_updated_board_game(int line)
{
    char **map = malloc(sizeof(char *) * (line + 3));
    int nb_col = nb_col_in_line(line);

    for (int i = 0; i < line + 2; i++) {
        map[i] = malloc(sizeof(char) * (nb_col + 1));
        map[i][0] = '*';
        map[i][nb_col - 1] = '*';
        map[i][nb_col] = '\0';
    }
    map = fil_tab(line, nb_col, map);
    return (map);
}