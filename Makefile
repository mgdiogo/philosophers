NAME	=	philo

RM		=	rm -rf
CC		=	cc
FLAGS	=	-Wall -Werror -Wextra -pthread -g
SRC		=	philo.c files/aux_functions.c \
			files/philo_functions.c files/philo_actions.c \
			files/philo_aux.c

OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(SRC) $(FLAGS) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all