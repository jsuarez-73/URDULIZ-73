# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 11:36:09 by jsuarez-          #+#    #+#              #
#    Updated: 2023/09/10 18:55:21 by jsuarez-         ###   ########.fr        #
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
SRCS_BONUS = ft_printf_bonus.c\
			ft_printf_nddrv_bonus.c\
			ft_printf_treedrv_bonus.c\
			ft_printf_parser_bonus.c\
			ft_printf_parser_utils_bonus.c\
			ft_printf_xpndr_bonus.c\
			ft_printf_xpndr_utils_bonus.c\
			ft_printf_outmch_bonus.c\
			ft_printf_strexp_bonus.c\
			ft_printf_dblexp_bonus.c\
			ft_printf_chrexp_bonus.c\
			ft_printf_hexexp_bonus.c\
			ft_printf_chexexp_bonus.c\
			ft_printf_usgnexp_bonus.c\
			ft_printf_ptrexp_bonus.c\
			ft_printf_perexp_bonus.c\
			ft_printf_wrmch_bonus.c

OBJS = $(SRCS:%.c=%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)
TEST_OBJ = $(TEST:%.c=%.o) 

$(NAME):
	@cc $(CLFAGS) -c $(SRCS)
	@ar -rcs $(NAME) $(OBJS)

all: $(NAME)

bonus:
	@cc $(CFLAGS) -c $(SRCS_BONUS)
	@ar -rcs $(NAME) $(OBJS_BONUS)

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)

fclean:
	@rm -f $(NAME)

re: fclean all

all_exec: $(NAME_EXEC)

$(NAME_EXEC): $(NAME)
	cc -c ./tests_main/$(TEST)
	cc -o $(NAME_EXEC) $(TEST_OBJ) $(NAME)

fcleang:
	@rm -f $(NAME_GDB)

fcleanx:
	@rm -f $(NAME_EXEC)


re_e: fcleanx all_exec exec

exec: clean
	@bash -c ./$(NAME_EXEC)

debug:
	@cc -g -o $(NAME_GDB) $(SRCS) $(TEST_OBJ)

xgdb: debug
	@gdb $(NAME_GDB)

vgd:
	@valgrind ./$(NAME_EXEC)

.PHONY: all clean fclean fcleang re \
		exec debug xgdb all_exec vgd \
		bonus
