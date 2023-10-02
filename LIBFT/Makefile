CFLAGS = -Wall -Werror -Wextra
NAME = libft.a
NAME_GDB = libft.gdb
SRCS = ft_bzero.c\
		ft_atoi.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_strchr.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\

SRCS_BONUS = ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c

SRCS_PRINTF = ft_printf.c\
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

SRCS_GNL = get_next_line.c\
			get_next_line_utils.c
PATH_PRINTF = $(foreach SRCS_PRINTF, $(SRCS_PRINTF), $(wildcard ../PRINTF/$(SRCS_PRINTF)));
PATH_GNL = ../GNL/get_next_line_utils.c ../GNL/get_next_line.c
OBJS = $(SRCS:%.c=%.o) $(SRCS_PRINTF:%.c=%.o) $(SRCS_GNL:%.c=%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

all : $(NAME)

$(NAME):
	cc $(CFLAGS) -c -I../PRINTF -I../GNL $(SRCS) $(SRCS_BONUS) $(PATH_GNL) \
		$(PATH_PRINTF)
	ar -rcs $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean:
	rm -rf $(NAME)

re: fclean all

bonus:
	cc $(CFLAGS) -c $(SRCS) $(SRCS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

debug:
	cc -g -o $(NAME_GDB) $(SRCS)

xgdb: debug
	gdb ./$(NAME_GDB)

.PHONY: all clean fclean re debug xgdb