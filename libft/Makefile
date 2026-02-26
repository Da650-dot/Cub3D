NAME    = libft.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -O2

SRC =	ft_strlen.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strtrim.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strjoin.c \
		ft_split.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isdigit.c \
		ft_isspace.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_bzero.c \
		ft_putstr_fd.c \
		ft_putchar_fd.c \
		get_next_line.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
