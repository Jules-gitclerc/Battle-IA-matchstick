##
## EPITECH PROJECT, 2019
## makefile_work
## File description:
## Makefile
##

SRCS = 	main.c
		generateur_map.c

NAME = my_sokoban

FLAGS += -Wall -Wextra

all : ${NAME}

${NAME} :
	gcc -o ${NAME} ${SRCS} -lncurses

clean :
	rm ${NAME}

fclean : clean

re : fclean all
