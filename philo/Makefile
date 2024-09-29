NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = includes
SRC = src/philo.c src/parse_input.c src/init_data.c src/mutex_handle.c src/dinner.c src/utils.c src/output.c src/monitor.c src/synchro_utils.c
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
