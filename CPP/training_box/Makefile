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

CFLAGS = -g -Wall -Wextra -Werror -std=c++98
FTYPE=.cpp
FSANITIZE_ON = -fsanitize=address
FSANITIZE_OFF = 
CC = g++
NAME =cpp
HEADERS_PATH = includes
INCLUDES = $(patsubst %, -I%, $(subst :, , $(HEADERS_PATH)))
OBJS_PATH = obj/
DEV_PATH = dev
SRC_PATH = src
BONUS_PATH = bonus
MANDATORY_PATH = mandatory
BETA_PATH = beta
BETA_EXCLUDE_M = %multiplex$(FTYPE) %hook$(FTYPE) %uminix$(FTYPE)
BETA_EXCLUDE = $(addsuffix _bonus$(FTYPE), %multiplex %hook %uminix)
UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
SO=LINUX
else ifeq ($(UNAME), Darwin)
SO=MAC
else

$(error OS not supported rey.)
endif

_headers_files = $(wildcard $(patsubst %, %/*.h, $(subst :, , $(HEADERS_PATH))))
_sources_files = $(wildcard $(SRC_PATH)/*$(FTYPE) $(SRC_PATH)/*/*$(FTYPE) $(SRC_PATH)/*/*/*$(FTYPE))
_objs_files = *.o
_objs_path_files = $(addprefix $(OBJS_PATH), $(_objs_files))
_dev_sources_files = $(wildcard $(DEV_PATH)/*$(FTYPE))
_mandatory_sources_files = $(wildcard $(MANDATORY_PATH)/*$(FTYPE) $(MANDATORY_PATH)/*/*$(FTYPE) $(MANDATORY_PATH)/*/*/*$(FTYPE))
_bonus_sources_files = $(wildcard $(BONUS_PATH)/*$(FTYPE) $(BONUS_PATH)/*/*$(FTYPE) $(BONUS_PATH)/*/*/*$(FTYPE))
_beta_sources_files = $(wildcard $(BETA_PATH)/*$(FTYPE) $(BETA_PATH)/*/*$(FTYPE) $(BETA_PATH)/*/*/*$(FTYPE))
_beta_sf_mandatory := $(filter-out %render_min$(FTYPE), $(_beta_sources_files))\
					  $(filter-out $(BETA_EXCLUDE_M), $(_mandatory_sources_files))
_beta_sources_files := $(filter-out %render_min_mandatory$(FTYPE), $(_beta_sources_files)) \
					   $(filter-out $(BETA_EXCLUDE), $(_bonus_sources_files))

ifeq ($(TEST_DEV),dev)
_sources_files:=$(subst main$(FTYPE),main_test$(FTYPE), $(_sources_files))
endif
#RULES

all : $(NAME)

_beta: $(NAME)

_bonus: $(NAME)

$(NAME): $(_objs_path_files) $(_headers_files)
	@$(CC) -o $(NAME) $(_objs_path_files) \
		$(FSANITIZE_OFF)
	@echo "$(GREEN)Executable file $(NAME) done!$(RESET)"

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

clean:
	@rm -rf $(_objs_path_files)
	@echo "$(BLUE)All objects rubish killed!$(RESET)"
	
fclean: clean
	@rm -rf $(NAME) $(OBJS_PATH)
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

