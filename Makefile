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
		src/shared/my_strtok.c \
		src/shared/my_strcmp.c \
		src/shared/my_strdup.c \
		src/shared/my_atoi.c \
		src/shared/my_isdigit.c \
		src/shared/my_strcpy.c \
		src/shared/my_atof.c \
		src/shared/my_itob.c \
		src/set_sprites.c \
		src/quadtree.c \
		src/draw.c
MAIN = src/main.c
OBJ = $(SRC:.c=.o)
CSFML = -lcsfml-graphics -lcsfml-system -lcsfml-window -lcsfml-audio -lm

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(MAIN) $(OBJ) $(CSFML) -g3
	make clean

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
