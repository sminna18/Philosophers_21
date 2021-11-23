NAME = philo

SRCS = philosophers.c  philo_func_1.c philo_func_2.c philo_func_3.c arg_checker.c ft_atoi.c

INCLUDE = philosophers.h

OBJS = $(SRCS:.c=.o)

CC = gcc 

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@  

$(NAME) : $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) -I./include -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: clean fclean re all