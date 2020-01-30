/*
** EPITECH PROJECT, 2019
** workshop_tournoi_ia
** File description:
** main.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "ia.h"

char **print_updated_board_game(int line);
void turn_ia(struct ia *ia, char **map, int line, int max_match);
int nb_col_in_line(int line);

int check_input_col_bis(int nb_col, char **map, int line, int nb_macht_p, char *name)
{
    int nb_col_p = 0;

    if (nb_col == 0) {
        endwin();
        printf("error: %s\n", name);
        exit (0);
    }
    for (int i = 1; map[line][i] != '*'; i++)
        if (map[line][i] == '|')
            nb_col_p++;
    if (nb_col > nb_col_p) {
        endwin();
        printf("error: %s\n", name);
        exit (0);
    }
    if (nb_col > nb_macht_p) {
        endwin();
        printf("error: %s\n", name);
        exit (0);
    }
}

int check_input_col(char **map, int line, int nb_macht_p, int nb_col, char *name)
{
    if (check_input_col_bis(nb_col, map, line, nb_macht_p, name) == -1)
        return (-1);
    return (nb_col);
}

int input_line_bis(int nb_line, char **map, int nb_line_max, int nb_macth_p, char *name)
{
    if (nb_line > nb_line_max) {
        endwin();
        printf("error: %s\n", name);
        exit (0);
    } else if (nb_line == 0) {
        endwin();
        printf("error: %s\n", name);
        exit (0);
    }
    for (int i = 1; map[nb_line][i] != '*'; i++)
        if (map[nb_line][i] == '|')
            nb_macth_p++;
    if (nb_macth_p <= 0) {
        endwin();
        printf("error: %s\n", name);
        exit (0);
    }
    return (0);
}

int check_input_line(char **map, int line, int nb_line, char *name)
{
    int nb_macth_p = 0;
    if (input_line_bis(nb_line, map, line, nb_macth_p, name) == -1)
        return (-1);
    return (nb_line);
}

int count_stick(char **map, int nb_line, int nb_colum)
{
    int nb = 0;

    for (int i = 0; i < nb_line + 2; i++)
        for (int o = 0; o < nb_colum; o++)
            if (map[i][o] == '|')
                nb++;
    if (nb == 0)
        return (0);
    else
        return (1);
}

char **board_game(int line, int nb_matches, char **map)
{
    int index = 1;

    for (; map[line][index] != '|'; index++);
    for (; map[line][index] != ' ' && map[line][index] != '*'; index++);
    for (int i = 0; i <= nb_matches; i++, index--)
        if (map[line][index] != '*')
            map[line][index] = ' ';
    return (map);
}

int main(int ac, char **av)
{
    int line = atoi(av[3]);
    char **map = print_updated_board_game(line);
    int row = 0;
    int col = nb_col_in_line(line) + 2;
    struct ia ia;
    int turn_ia_playeur = 1;
    int lose_ia_1 = 0;
    int lose_ia_2 = 0;
    int max_macht = 20;

    ia.line = 0;
    ia.macht = 0;
    initscr();
    noecho();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    getmaxyx(stdscr, row, col);
    row = (row - ((line + 2) / 2) * 2) / 2;
    attron(COLOR_PAIR(1));
    mvprintw(2, 13, "%s\n", av[1]);
    attroff(COLOR_PAIR(1));
    mvprintw(7, 3, "%s = %d\n", "LINE", ia.line);
    mvprintw(8, 3, "%s = %d\n", "MACHT", ia.macht);
    mvprintw(9, 3, "Player removed %i match(es) from line %i\n", ia.macht, ia.line);
    for (int i = 0; i < line + 2; i++, row++)
        mvprintw(row, (col - strlen(map[i])) / 2, "%s\n", map[i]);
    attron(COLOR_PAIR(2));
    mvprintw(2, 175, "%s\n", av[2]);
    attroff(COLOR_PAIR(1));
    mvprintw(6 + 1, 160 - 3, "%s = %d\n", "LINE", ia.line);
    mvprintw(7 + 1, 160 - 3, "%s = %d\n", "MACHT", ia.macht);
    mvprintw(8 + 1, 160 - 3, "Player removed %i match(es) from line %i\n", ia.macht, ia.line);
    getch();
    refresh();
    while (1) {
        if (turn_ia_playeur == 1 && lose_ia_1 == 0) {
            turn_ia(&ia, map, line, max_macht);
            check_input_line(map, line, ia.line, av[1]);
            check_input_col(map, ia.line, max_macht, ia.macht, av[1]);
            map = board_game(ia.line, ia.macht, map);
            if (count_stick(map, line, col) == 0) {
                lose_ia_1 = 1;
                break;
            }
        } else if (turn_ia_playeur == 2 && lose_ia_2 == 0) {
            turn_ia(&ia, map, line, max_macht);
            check_input_line(map, line, ia.line, av[2]);
            check_input_col(map, ia.line, max_macht, ia.macht, av[2]);
            map = board_game(ia.line, ia.macht, map);
            if (count_stick(map, line, col) == 0) {
                lose_ia_2 = 1;
                break;
            }
        }
        getmaxyx(stdscr, row, col);
        row = (row - ((line + 2) / 2) * 2) / 2;
        mvprintw(2, 13, "%s\n", av[1]);
        mvprintw(7, 3, "%s = %d\n", "LINE", ia.line);
        mvprintw(8, 3, "%s = %d\n", "MACHT", ia.macht);
        mvprintw(9, 3, "Player removed %i match(es) from line %i\n", ia.macht, ia.line);
        for (int i = 0; i < line + 2; i++, row++)
            mvprintw(row, (col - strlen(map[i])) / 2, "%s\n", map[i]);
        mvprintw(2, 175, "%s\n", av[2]);
        mvprintw(6 + 1, 160 - 3, "%s = %d\n", "LINE", ia.line);
        mvprintw(7 + 1, 160 - 3, "%s = %d\n", "MACHT", ia.macht);
        mvprintw(8 + 1, 160 - 3, "Player removed %i match(es) from line %i\n", ia.macht, ia.line);
        turn_ia_playeur += 1;
        if (turn_ia_playeur > 2)
            turn_ia_playeur = 1;
        for(int i = 0; i < 100000000; i++);
        refresh();
        ia.line = 0;
        ia.macht = 0;
    }
    getmaxyx(stdscr, row, col);
    row = (row - ((line + 2) / 2) * 2) / 2;
    mvprintw(2, 13, "%s\n", av[1]);
    mvprintw(7, 3, "%s = %d\n", "LINE", ia.line);
    mvprintw(8, 3, "%s = %d\n", "MACHT", ia.macht);
    mvprintw(9, 3, "Player removed %i match(es) from line %i\n", ia.macht, ia.line);
    for (int i = 0; i < line + 2; i++, row++)
        mvprintw(row, (col - strlen(map[i])) / 2, "%s\n", map[i]);
    mvprintw(2, 175, "%s\n", av[2]);
    mvprintw(6 + 1, 160 - 3, "%s = %d\n", "LINE", ia.line);
    mvprintw(7 + 1, 160 - 3, "%s = %d\n", "MACHT", ia.macht);
    mvprintw(8 + 1, 160 - 3, "Player removed %i match(es) from line %i\n", ia.macht, ia.line);
    if (lose_ia_2 == 1) {
        mvprintw(33, 160 - 3, "GAME OVER");
        mvprintw(33, 3, "WINNER");
    } else {   
        mvprintw(33, 160 - 3, "WINNER");
        mvprintw(33, 3, "GAME OVER");
    }
    refresh();
    getch();
    endwin();
    if (lose_ia_2 == 1)
        printf("IA of %s win\n", av[1]);
    else
        printf("IA of %s win\n", av[2]);
    return (0);
}
