# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 11:36:09 by jsuarez-          #+#    #+#              #
#    Updated: 2023/08/26 21:13:48 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
NAME = ft_printf.jsb
NAME_GDB = ft_printf.gdb
SRCS = ft_printf.c\
		ft_printf_nddrv.c\
		ft_printf_treedrv.c\
		ft_printf_parser.c\
		ft_printf_parser_utils.c\
		ft_printf_xpndr_utils.c
OBJS = $(SRCS:%.c=%.o)

$(NAME):
	cc $(CFLAGS) -c $(SRCS)
	cc -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean:
	rm -f $(NAME)

fcleang:
	rm -f $(NAME_GDB)

re: fclean all

re_e: fclean all exec

exec: clean
	bash -c ./$(NAME)

debug:
	cc -g $(CFLAGS) -o $(NAME_GDB) $(SRCS)

xgdb: debug
	gdb $(NAME_GDB)

.PHONY: all clean fclean fcleang re exec debug xgdb
