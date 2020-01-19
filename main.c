/*
** EPITECH PROJECT, 2019
** workshop_tournoi_ia
** File description:
** main.c
*/

#include <stdio.h>
#include <string.h>
#include <ncurses.h>

char **print_updated_board_game(int line);
int nb_col_in_line(int line);

int main(int ac, char **av)
{
    int line = 53;
    char **map = print_updated_board_game(line);
    int row = 0;
    int y = 0;
    int col = nb_col_in_line(line) + 2;

    initscr();
    noecho();
    getmaxyx(stdscr, row, col);
    y = row;
    row = (row - ((line + 2) / 2) * 2) / 2;
    mvprintw(2, 13, "%s\n", "PLAYEUR ONE");
    mvprintw(35, 13, "%s\n", "PLAYEUR THREE");
    for (int i = 0; i < line + 2; i++, row++)
        mvprintw(row, (col - strlen(map[i])) / 2, "%s\n", map[i]);
    mvprintw(2, 175, "%s\n", "PLAYEUR TWO");
    mvprintw(35, 175, "%s\n", "PLAYEUR FOUR");
    getch();
    refresh();
    endwin();
    return (0);
}
