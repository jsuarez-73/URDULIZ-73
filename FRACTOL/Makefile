# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/21 17:45:11 by jsuarez-          #+#    #+#              #
#    Updated: 2023/10/01 15:29:54 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC = cc
NAME = fractol.jsb
SRCS = fractol.c\
		color_scheme.c\
		event_mchn.c\
		render_mchn.c\
		init.c
SRCS_SETS = ft_julia.c\
			ft_mondelbrot.c\
			ft_cubic.c
SRCS_UTILS = ft_atof.c\
				ft_help_msg.c
PATH_SETS = $(foreach SRCS_SETS, $(SRCS_SETS), $(wildcard sets/$(SRCS_SETS)));
PATH_UTILS = utils/ft_atof.c utils/ft_help_msg.c
LIBS = libs/
OBJ = $(SRCS:%.c=%.o)
OBJ_SETS = $(SRCS_SETS:%.c=%.o)
OBJ_UTILS = $(SRCS_UTILS:%.c=%.o)
#This rule make each .c file a .o file looking for headers in the paths
#usr/include and mlx_linux
# %.o:%.c
# 	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@
#This rule add with -L option for gcc the directories especified by the path
#during the preprocessing, then with -l option in linking stage they can look
#for the files needed, so in this rule they took every OBJ file and link them
#with the libraries and header files.
#The other way it was needed the object files created in compilation time so
#it was easier creating the libraries and just attaching them.
$(NAME):
	$(CC) -g -c $(CFLAGS) -Iincludes -Imlx_linux $(SRCS) $(PATH_UTILS) $(PATH_SETS)
	$(CC) $(OBJ) $(OBJ_SETS) $(OBJ_UTILS) $(LIBS)libmlx_Linux.a $(LIBS)libmlx.a \
		$(LIBS)libft.a -lXext -lX11 -lm -lz -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ) $(OBJ_SETS) $(OBJ_UTILS)

fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean re fclean