
SRCS	= main.c error.c init.c utils.c processing.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo_bonus

GCC	= gcc

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -pthread

HEADER	= philo.h

all:	$(NAME)

.PHONY:	clean fclean re

$(NAME): $(OBJS)
	$(GCC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c $(HEADER)
	$(GCC) $(FLAGS) -c $<  -o $(<:.c=.o)
