NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = include

SRC_DIR = src
SRC = philo.c init_data.c start_dinner.c utils.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJ = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re