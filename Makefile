NAME := philo

CC := gcc

CFLAGS := -Wall -Wextra -Werror -pthread -g

SRC = ft_check.c \
ft_error.c \
main.c \
init.c \
time.c \
routine.c \
thread.c \
print_output.c \
ft_check_finish.c \
ft_free.c \
ft_error_init.c \
init_philo.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
