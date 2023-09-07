# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 11:36:09 by jsuarez-          #+#    #+#              #
#    Updated: 2023/09/07 17:23:56 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
NAME = libftprintf.a
NAME_EXEC = ft_printf.jsb
NAME_GDB = ft_printf.gdb
SRCS = ft_printf.c\
		ft_printf_nddrv.c\
		ft_printf_treedrv.c\
		ft_printf_parser.c\
		ft_printf_parser_utils.c\
		ft_printf_xpndr.c\
		ft_printf_xpndr_utils.c\
		ft_printf_outmch.c\
		ft_printf_strexp.c\
		ft_printf_dblexp.c\
		ft_printf_chrexp.c\
		ft_printf_hexexp.c\
		ft_printf_chexexp.c\
		ft_printf_usgnexp.c\
		ft_printf_ptrexp.c\
		ft_printf_perexp.c\
		ft_printf_wrmch.c

OBJS = $(SRCS:%.c=%.o)

$(NAME):
	cc -c $(SRCS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

all_exec: $(NAME_EXEC)

$(NAME_EXEC):
	cc -c $(SRCS)
	cc -o $(NAME_EXEC) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean:
	rm -f $(NAME)

fcleang:
	rm -f $(NAME_GDB)

fcleanx:
	rm -f $(NAME_EXEC)

re: fclean all

re_e: fcleanx all_exec exec

exec: clean
	bash -c ./$(NAME_EXEC)

debug:
	gcc -g -o $(NAME_GDB) $(SRCS)

xgdb: debug
	gdb $(NAME_GDB)

vgd:
	valgrind ./$(NAME_EXEC)
# .PHONY: all clean fclean re
.PHONY: all clean fclean fcleang re \
		exec debug xgdb all_exec vgd
