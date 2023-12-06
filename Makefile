##
## EPITECH PROJECT, 2023
## B-MUL-100-LYN-1-1-myradar-hugo.cathelain
## File description:
## Makefile
##

NAME = my_radar
SRC =   src/radar.c \
		src/shared/my_strlen.c
MAIN = src/main.c
OBJ = $(SRC:.c=.o)
FLAG_TEST = -Iinclude --coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(MAIN) $(OBJ) -g3
	make clean

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run:
	gcc -o unit_tests tests/testing.c $(SRC) $(FLAG_TEST)
	make clean
	./unit_tests && gcovr -e tests/ && gcovr -e tests/ -b

tests_clean:
	rm -f unit_tests && rm -f *.gcno && rm -f *.gcda
