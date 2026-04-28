##
## EPITECH PROJECT, 2026
## WOLFENSTEIN3D
## File description:
## Makefile for building the wolf3d project
##

CC = epiclang
LDFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm
CFLAGS = -Wall -Wextra -Werror -I.

SRC = src/main.c \
	src/window.c \
	src/map.c \
	src/menu.c
	src/player.c \
	src/wolf3d.c
OBJ = $(SRC:.c=.o)

all: wolf3d

wolf3d: $(OBJ)
	$(CC) -o wolf3d $(OBJ) $(LDFLAGS) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f wolf3d

re: fclean all

.PHONY: all clean fclean re
