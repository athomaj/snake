##
## Makefile for  in /Users/julien/ClionProjects/snake JD
## 
## Made by julien athomas
## Login   <julien@epitech.net>
## 
## Started on  Thu Apr 16 23:27:27 2015 julien athomas
## Last update Mon May  4 10:38:29 2015 julien athomas
##

SRC=	main.c	\
	snake.c	\
	display.c \

OBJ=	$(SRC:.c=.o)

NAME=	bin

CFLAGS=	-W -Wall -Wextra -Werror -g3

LIB=	 -lSDL

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ) $(LIB)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all
