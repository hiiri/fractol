# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 20:45:50 by alcohen           #+#    #+#              #
#    Updated: 2020/08/10 19:17:23 by alcohen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
NAME = fractol

MAIN = main.c
SRCS = $(MAIN) draw.c handle_input.c gui.c colors.c handle_keys.c julia.c
OBJS=$(notdir $(SRCS:.c=.o))
LIBFT = libft/libft.a
MAKE_LIB=make -C libft/ fclean && make -C libft/
MLX = -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL \
-framework AppKit

all: $(NAME)

linux:
	@$(MAKE_LIB)
	gcc -c $(SRCS)
	gcc $(FLAGS) $(OBJS) minilibx/libmlx_Linux.a -lm -lX11 -lXext -pthread -o $(NAME) $(LIBFT)

noflags:
	@$(MAKE_LIB)
	gcc -c $(SRCS)
	gcc $(MLX) -o $(NAME) $(OBJS) $(LIBFT)

$(NAME):
	@$(MAKE_LIB)
	gcc $(FLAGS) -c $(SRCS)
	gcc $(FLAGS) $(MLX) -o $(NAME) $(OBJS) $(LIBFT)

re: fclean $(NAME)

clean:
	/bin/rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean
