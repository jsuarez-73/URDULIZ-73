# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 20:09:14 by jsuarez-          #+#    #+#              #
#    Updated: 2023/10/16 20:41:28 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS= -Wall -Wextra -Werror
NAME= push_swap
CC= gcc
MACHINE=$(shell uname)
ifeq ($(MACHINE), Linux)
	MACHINE = LINUX
endif
ifeq ($(MACHINE), Darwin)
	MACHINE = MAC
endif
SRCS = push_swap.c
OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME): | libs
	$(CC) -c -g $(CFLAGS) -D $(MACHINE) -Iincludes $(addprefix src/, $(SRCS))
	$(CC) -o $(NAME) $(OBJS) libs/libft.a

libs:
	make -C libft/LIBFT
	mkdir libs
	mv libft/LIBFT/libft.a libs/
	make -C libft/LIBFT clean

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean re fclean
