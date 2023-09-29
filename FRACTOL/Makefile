# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/21 17:45:11 by jsuarez-          #+#    #+#              #
#    Updated: 2023/09/29 20:50:58 by jsuarez-         ###   ########.fr        #
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
PATH_SRCS = $(foreach SRCS_SETS, $(SRCS_SETS), $(wildcard sets/$(SRCS_SETS)));
LIBS = libs/
OBJ = $(SRCS:%.c=%.o)
OBJ_SETS = $(SRCS_SETS:%.c=%.o)
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
	$(CC) -g -c $(CFLAGS) -Iincludes -Imlx_linux $(SRCS) $(PATH_SRCS)
	$(CC) $(OBJ) $(OBJ_SETS) $(LIBS)libmlx_Linux.a $(LIBS)libmlx.a $(LIBS)libft.a -lXext -lX11 -lm -lz -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ) $(OBJ_SETS)

fclean:
	rm -rf $(NAME)

re: fclean all

atof:
	$(CC) -g -c $(CFLAGS) -Iincludes ft_atof.c
	$(CC) ft_atof.o $(LIBS)libft.a -o Xatof
 .PHONY: all clean re fclean