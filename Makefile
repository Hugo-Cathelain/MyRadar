##
## EPITECH PROJECT, 2023
## B-MUL-100-LYN-1-1-myradar-hugo.cathelain
## File description:
## Makefile
##

NAME = my_radar
SRC =   src/radar.c \
		src/shared/my_strlen.c \
		src/shared/my_putstr.c \
		src/set_sprites.c
MAIN = src/main.c
OBJ = $(SRC:.c=.o)
CSFML = -lcsfml-graphics -lcsfml-system -lcsfml-window -lcsfml-audio

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(MAIN) $(OBJ) $(CSFML) -g3
	make clean

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
