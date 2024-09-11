NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = includes
SRC = src/philo.c src/parse_input.c src/init_data.c src/mutex_handle.c src/dinner.c src/utils.c src/output.c src/monitor.c src/synchro_utils.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

all: $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
