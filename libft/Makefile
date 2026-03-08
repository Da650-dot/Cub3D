# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabriede <gabriede@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 17:20:29 by gabriede          #+#    #+#              #
#    Updated: 2026/03/08 19:18:53 by gabriede         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = 	ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_memcpy.c ft_memmove.c ft_strlen.c ft_memset.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
		ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		get_next_line.c get_next_line_utils.c   # ← Adicionado aqui

BSRCS = ft_lstnew.c ft_lstadd_front.c \
		ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

HEADER = libft.h

OBJS = ${SRCS:.c=.o}
BOJS = ${BSRCS:.c=.o}

FLAGS = -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

bonus: ${OBJS} ${BOJS}
	ar rcs ${NAME} ${OBJS} ${BOJS}

%.o: %.c ${HEADER}
	cc ${FLAGS} -c $< -o $@

clean:
	rm -f ${OBJS} ${BOJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus