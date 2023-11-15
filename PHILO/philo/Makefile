# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 17:24:18 by jsuarez-          #+#    #+#              #
#    Updated: 2023/11/15 19:37:00 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC = gcc
NAME = philo
SRCS = philo.c\
		check_args.c\
		utils.c\
		philo_life.c\
		init.c\
		create_flush_th.c
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