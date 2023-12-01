# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 19:26:50 by jsuarez-          #+#    #+#              #
#    Updated: 2023/12/01 16:00:55 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
FSANITIZE_ON = -fsanitize=thread
FSANITIZE_OFF = 
CC = gcc
NAME = philo_bonus
SRCS = philo_bonus.c\
		check_args_bonus.c\
		flusher.c\
		init_bonus.c\
		launcher.c\
		philo_life_bonus.c\
		push_log.c\
		semaphores_utils.c\
		utils_bonus.c\
		ft_usleep.c
OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(FSANITIZE_OFF) $(OBJS)

$(OBJS): $(addprefix src/, $(SRCS))
	$(CC) -c -g $(CFLAGS) $(FSANITIZE_OFF) -Iincludes $(addprefix src/, $(SRCS))

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re