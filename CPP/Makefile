# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uurbizu- <uurbizu-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 19:50:42 by jsuarez-          #+#    #+#              #
#    Updated: 2024/06/20 21:47:44 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#VARIABLES

CFLAGS = -g -Wall -Wextra -Werror
FSANITIZE_ON = -fsanitize=address
FSANITIZE_OFF = 
CC = gcc
NAME = miniRT
INCLUDES = $(patsubst %, -I%, $(subst :, , $(HEADERS_PATH)))
LIBFT_PATH=libft/
MINILIBX_LINUX_PATH=lib/minilibx-linux/
MINILIBX_MAC_PATH=lib/minilibx_opengl_20191021/
OBJS_PATH = obj/
DEV_PATH = dev
SRC_PATH = src
BONUS_PATH = bonus
MANDATORY_PATH = mandatory
BETA_PATH = beta
BETA_EXCLUDE_M = %multiplex.c %hook.c %uminix.c
BETA_EXCLUDE = $(addsuffix _bonus.c, %multiplex %hook %uminix)
LIB = libft.a
MINILIBX_LIB = libmlx.a
UNAME = $(shell uname)

ifeq ($(UNAME), Linux)

MINILIBX_PATH = $(MINILIBX_LINUX_PATH)
MLXFLAGS	:= 	-L $(MINILIBX_PATH) -lmlx -lXext -lX11 -lm
HEADERS_PATH = includes:$(lastword $(dir $(MINILIBX_LINUX_PATH)))
SO=LINUX
else ifeq ($(UNAME), Darwin)

MINILIBX_PATH = $(MINILIBX_MAC_PATH)
MLXFLAGS	:= 	-L $(MINILIBX_PATH) -lmlx -Ilmlx -framework OpenGL -framework AppKit
HEADERS_PATH = includes:$(lastword $(dir $(MINILIBX_MAC_PATH)))
SO=MAC
else

$(error OS not supported rey.)
endif

_headers_files = $(wildcard $(patsubst %, %/*.h, $(subst :, , $(HEADERS_PATH))))
_sources_files = $(wildcard $(SRC_PATH)/*.c $(SRC_PATH)/*/*.c $(SRC_PATH)/*/*/*.c)
_objs_files = *.o
_objs_path_files = $(addprefix $(OBJS_PATH), $(_objs_files))
_libft_path = $(addprefix $(LIBFT_PATH), $(LIB))
_minilibx-linux = $(addprefix $(MINILIBX_PATH), $(MINILIBX_LIB))
_dev_sources_files = $(wildcard $(DEV_PATH)/*.c)
_mandatory_sources_files = $(wildcard $(MANDATORY_PATH)/*.c $(MANDATORY_PATH)/*/*.c $(MANDATORY_PATH)/*/*/*.c)
_bonus_sources_files = $(wildcard $(BONUS_PATH)/*.c $(BONUS_PATH)/*/*.c $(BONUS_PATH)/*/*/*.c)
_beta_sources_files = $(wildcard $(BETA_PATH)/*.c $(BETA_PATH)/*/*.c $(BETA_PATH)/*/*/*.c)
_beta_sf_mandatory := $(filter-out %render_min.c, $(_beta_sources_files))\
					  $(filter-out $(BETA_EXCLUDE_M), $(_mandatory_sources_files))
_beta_sources_files := $(filter-out %render_min_mandatory.c, $(_beta_sources_files)) \
					   $(filter-out $(BETA_EXCLUDE), $(_bonus_sources_files))

ifeq ($(TEST_DEV),dev)
_sources_files:=$(subst main.c,main_test.c, $(_sources_files))
endif
#RULES

all : $(NAME)

_beta: $(NAME)

_bonus: $(NAME)

$(NAME): $(_objs_path_files) $(_minilibx-linux) $(_libft_path) $(_headers_files)
	@$(CC) -o $(NAME) $(_objs_path_files) $(_libft_path) $(_minilibx-linux) $(MLXFLAGS)\
		$(FSANITIZE_OFF)
	@echo "$(GREEN)Executable file miniRT done!$(RESET)"

$(_objs_path_files): $(_sources_files) $(if $(BONUS), $(_bonus_sources_files)) \
						$(if $(BETA), $(_beta_sources_files)) $(_headers_files) \
						$(if $(or $(BONUS), $(BETA)),, $(_mandatory_sources_files))
	$(CC) -D $(SO) -c $(CFLAGS) $(FSANITIZE_OFF) $(INCLUDES) $(_sources_files) \
		$(if $(DEVELOP), $(_dev_sources_files)) $(if $(BONUS), \
		$(_bonus_sources_files)) $(if $(BETA), $(_beta_sources_files)) \
		$(if $(or $(BONUS), $(BETA), $(BETA_M)),, $(_mandatory_sources_files)) \
		$(if $(BETA_M), $(_beta_sf_mandatory))
	@mkdir -p $(OBJS_PATH)
	@mv $(_objs_files) $(OBJS_PATH)
	@echo "$(GREEN)Objects files created! $(RESET)"

$(_libft_path):
	@make -C lib/LIBFT
	@mkdir -p libft
	@mv lib/LIBFT/libft.a ./libft/
	@make -C lib/LIBFT clean
	@echo "$(GREEN)Libft compiled!$(RESET)"

$(_minilibx-linux):
	@make -C $(MINILIBX_PATH)
	@echo "$(GREEN)miniLibx compiled!$(RESET)"

clean:
	@rm -rf $(_objs_files)
	@make -C $(MINILIBX_PATH) clean
	@echo "$(BLUE)All objects rubish killed!$(RESET)"
	
fclean: clean
	@rm -rf $(NAME) $(LIBFT_PATH) $(OBJS_PATH)
	@echo "$(BLUE)File executable and library killed!$(RESET)"

re: fclean all

dev:
	make DEVELOP=DEFINED all

bonus:
	make BONUS=DEFINED _bonus

dev_bonus:
	make BONUS=DEFINED DEVELOP=DEFINED _bonus

beta:
	make BETA=DEFINED _beta

beta_m:
	make BETA_M=DEFINED _beta

dev_beta:
	make BETA=DEFINED DEVELOP=DEFINED _beta

.PHONY: all fclean clean re bonus dev beta dev_beta dev_bonus beta_m

#COLORS

GREEN = \033[32m
RED = \033[31m
BLUE = \033[36m
RESET = \033[0m

