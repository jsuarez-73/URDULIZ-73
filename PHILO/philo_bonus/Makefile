# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 19:26:50 by jsuarez-          #+#    #+#              #
#    Updated: 2023/11/17 08:22:59 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = philo_bonus
SRCS = philo_bonus.c\
		check_args.c
OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

$(OBJS): $(addprefix src/, $(SRCS))
	$(CC) -c -g $(CFLAGS) -Iincludes $(addprefix src/, $(SRCS))

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re