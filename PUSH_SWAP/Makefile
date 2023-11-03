# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 20:09:14 by jsuarez-          #+#    #+#              #
#    Updated: 2023/11/03 09:10:10 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS= -Wall -Wextra -Werror
NAME= push_swap
BONUS_NAME = checker
CC= gcc
MACHINE=$(shell uname)
ifeq ($(MACHINE), Linux)
	MACHINE = LINUX
endif
ifeq ($(MACHINE), Darwin)
	MACHINE = MAC
endif
SRCS = push_swap.c\
		stacka_utils.c\
		stackb_utils.c\
		common_utils.c\
		desicion_utils.c\
		init_utils.c\
		math_utils.c\
		mastermind.c
BONUS = checker.c\
		checker_init_utils.c\
		checker_exec_utils.c
COMMON = init_utils.c\
			common_utils.c\
			stacka_utils.c\
			stackb_utils.c\
			math_utils.c
OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(BONUS:%.c=%.o)
CMN_OBJS = $(COMMON:%.c=%.o)

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
	rm -rf $(OBJS) $(BONUS_OBJS) $(CMN_OBJS)

fclean:
	rm -rf $(NAME)

bonus: | libs
	$(CC) -c -g $(CFLAGS) -D $(MACHINE) -Iincludes $(addprefix bonus/, $(BONUS)) \
	$(addprefix src/, $(COMMON))
	$(CC) -o $(BONUS_NAME) $(BONUS_OBJS) $(CMN_OBJS) libs/libft.a

re: fclean all

.PHONY: all clean re fclean bonus
