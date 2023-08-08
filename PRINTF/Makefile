# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 11:36:09 by jsuarez-          #+#    #+#              #
#    Updated: 2023/08/08 21:17:49 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
NAME = ft_printf.jsb
SRCS = ft_printf.c\
		ft_printf_nddrv.c\
		ft_printf_treedrv.c
OBJS = $(SRCS:%.c=%.o)

$(NAME):
	cc $(CFLAGS) -c $(SRCS)
	cc -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean:
	rm -f $(NAME)

re: fclean all

re_e: fclean all exec

exec: clean
	bash -c ./$(NAME)

.PHONY: all clean fclean re exec
