# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 18:37:59 by jsuarez-          #+#    #+#              #
#    Updated: 2023/10/09 21:04:08 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
CC = gcc
NAME_SRVR = server
NAME_CLNT = client
MACHINE = $(shell uname)
ifeq ($(MACHINE), Linux)
	MACHINE = LINUX
endif
ifeq ($(MACHINE), Darwin)
	MACHINE = MAC
endif
SRCS_SRVR = server.c
OBJS_SRVR = $(SRCS_SRVR:%.c=%.o)
SRCS_CLNT = client.c
OBJS_CLNT = $(SRCS_CLNT:%.c=%.o)
all : $(NAME_SRVR) $(NAME_CLNT)

ifeq ($(MACHINE), LINUX)
$(NAME_SRVR): | libs
	$(CC) -g -D $(MACHINE) $(CFLAGS) -c -Iincludes $(addprefix src/, $(SRCS_SRVR))
	$(CC) -o $(NAME_SRVR) $(OBJS_SRVR) libs/libft.a
	rm -rf $(OBJS_SRVR)

$(NAME_CLNT): | libs
	$(CC) -g -D $(MACHINE) $(CFLAGS) -c -Iincludes $(addprefix src/, $(SRCS_CLNT))
	$(CC) -o $(NAME_CLNT) $(OBJS_CLNT) libs/libft.a
	rm -rf $(OBJS_CLNT)
endif

libs :
	make -C libft/LIBFT
	mkdir libs
	mv libft/LIBFT/libft.a libs/
	make -C libft/LIBFT clean

clean :
	rm -rf $(OBJS)

fclean :
	rm -rf $(NAME_CLNT) $(NAME_SRVR)

re : fclean all

.PHONY: clean fclean re all