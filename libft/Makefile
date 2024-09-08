NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
PRINTF_DIR = ft_printf/src
LIBFT_SRC = libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c \
libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c \
libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c \
libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c \
libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c \
libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c \
libft/ft_lstadd_back.c libft/ft_lstadd_front.c libft/ft_lstclear.c \
libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstlast.c libft/ft_lstmap.c libft/ft_lstnew.c libft/ft_lstsize.c
PRINTF_SRC = $(PRINTF_DIR)/c_specifier.c $(PRINTF_DIR)/d_specifier.c $(PRINTF_DIR)/digit.c $(PRINTF_DIR)/flags.c $(PRINTF_DIR)/ft_printf.c \
$(PRINTF_DIR)/my_atoi.c $(PRINTF_DIR)/p_specifier.c $(PRINTF_DIR)/put_result.c $(PRINTF_DIR)/s_specifier.c $(PRINTF_DIR)/u_specifier.c $(PRINTF_DIR)/x_specifier.c
GNL_SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)
PRINTF_OBJ = $(PRINTF_SRC:.c=.o)
GNL_OBJ = $(GNL_SRC:.c=.o)
INCLUDE = includes

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME): $(LIBFT_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)
	ar rc $(NAME) $(LIBFT_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)

all: $(NAME)

clean: 
	rm -f $(LIBFT_OBJ) $(PRINTF_OBJ) $(GNL_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all