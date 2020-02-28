# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 13:37:21 by alcohen           #+#    #+#              #
#    Updated: 2020/02/25 16:30:42 by alcohen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c \
	   ft_isdigit.c \
	   ft_putchar.c \
	   ft_putchar_fd.c \
	   ft_putendl.c \
	   ft_putendl_fd.c \
	   ft_putstr.c \
	   ft_putstr_fd.c \
	   ft_strcmp.c \
	   ft_strncmp.c \
	   ft_strlen.c \
	   ft_putnbr.c \
	   ft_putnbr_fd.c \
	   ft_isalpha.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_isprint.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_strequ.c \
	   ft_strnequ.c \
	   ft_strcpy.c \
	   ft_strncpy.c \
	   ft_strdup.c \
	   ft_strmap.c \
	   ft_strmapi.c \
	   ft_striter.c \
	   ft_striteri.c \
	   ft_strsub.c \
	   ft_iswhitespace.c \
	   ft_strtrim.c \
	   ft_itoa.c \
	   ft_strrev.c \
	   ft_memdel.c \
	   ft_strnew.c \
	   ft_strdel.c \
	   ft_strclr.c \
	   ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_memccpy.c \
	   ft_memmove.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_strcat.c \
	   ft_strncat.c \
	   ft_strlcat.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strstr.c \
	   ft_strnstr.c \
	   ft_strsplit.c \
	   ft_strjoin.c \
	   ft_memalloc.c \
	   get_next_line.c \
	   ft_atoilong.c \

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

$(NAME):
	@gcc $(FLAGS) -c $(SRCS)
	@ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
