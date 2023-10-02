# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/21 17:45:11 by jsuarez-          #+#    #+#              #
#    Updated: 2023/10/02 17:32:35 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC = cc
MACHINE = $(shell uname)
ifeq ($(MACHINE), Linux)
	MACHINE = LINUX
endif
ifeq ($(MACHINE), Darwin)
	MACHINE = MAC
endif
NAME = fractol
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
PATH_SRCS = $(foreach SRCS, $(SRCS), $(wildcard src/$(SRCS)))
PATH_SETS = sets/ft_julia.c sets/ft_mondelbrot.c sets/ft_cubic.c
PATH_UTILS = utils/ft_atof.c utils/ft_help_msg.c
LIBS = libs/
OBJ = $(SRCS:%.c=%.o)
OBJ_SETS = $(SRCS_SETS:%.c=%.o)
OBJ_UTILS = $(SRCS_UTILS:%.c=%.o)
#This rule make each .c file a .o file looking for headers in the paths
#usr/include and mlx_linux
# %.o:%.c
#   $(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@
#This rule add with -L option for gcc the directories especified by the path
#during the preprocessing, then with -l option in linking stage they can look
#for the files needed, so in this rule they took every OBJ file and link them
#with the libraries and header files.
#The other way it was needed the object files created in compilation time so
#it was easier creating the libraries and just attaching them.
# LINUX COMPILATION
ifeq ($(MACHINE), LINUX)
$(NAME): lib_linux
	$(CC) -g -D $(MACHINE) -c $(CFLAGS) -Iincludes -Imlx_linux $(PATH_SRCS) \
		$(PATH_UTILS) $(PATH_SETS)
	$(CC) $(OBJ) $(OBJ_SETS) $(OBJ_UTILS) $(LIBS)libmlx_Linux.a $(LIBS)libmlx.a \
		$(LIBS)libft.a -lXext -lX11 -lm -lz -o $(NAME)
endif
# MAC COMPILATION

ifeq ($(MACHINE), MAC)
$(NAME):lib
	$(CC) -g -D $(MACHINE) -c $(CFLAGS) -Iincludes -Imlx_mac $(PATH_SRCS) \
		$(PATH_UTILS) $(PATH_SETS)
	$(CC) $(OBJ) $(OBJ_SETS) $(OBJ_UTILS) $(LIBS)libmlx.a $(LIBS)libft.a \
		-framework OpenGL -framework AppKit -o $(NAME)
endif

all: $(NAME)

lib_linux:
	make -C libft/LIBFT
	make -C mlx_linux
	mkdir libs
	mv libft/LIBFT/libft.a libs/
	mv mlx_linux/libmlx.a libs/
	mv mlx_linux/libmlx_Linux.a libs/

lib:
	make -C libft/LIBFT
	make -C mlx_mac
	mkdir libs
	mv libft/LIBFT/libft.a libs/
	mv mlx_mac/libmlx.a libs/

clean:
	rm -rf $(OBJ) $(OBJ_SETS) $(OBJ_UTILS)
	make -C libft/LIBFT clean fclean
	make -C mlx_mac/ clean
	make -C mlx_linux/ clean
	rm -rf libs/

fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean re fclean lib