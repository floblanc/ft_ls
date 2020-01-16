# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/21 10:08:34 by maginist          #+#    #+#              #
#    Updated: 2020/01/16 10:53:32 by floblanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC_NAME =	main.c 				\

SRC_PATH = ./src/

OBJ_PATH = ./obj/

INC_PATH = ./include/

INC_NAME =	ft_ls.h


LIBFT				=	./libftprintf/
LIBFTA				=	libprintf.a
LIBFTINCLUDES		=	./libftprintf/include/

CC = gcc

CFLAGS = -Wall -Werror -Wextra

# Colors
CK = $'\033[30m$'
_RED = $'\033[31m$'
_GREEN = $'\033[32m$'
_YELLOW = $'\033[33m$'
_BLUE = $'\033[34m$'
_PURPLE = $'\033[35m$'
_CYAN = $'\033[36m$'
_GREY = $'\033[37m$'
_END=$'\033[0m$'


INC	= $(addprefix $(INC_PATH), $(INC_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

.PHONY :	all clean fclean re

all: $(NAME)

$(LIBFT)/$(LIBFTA):
	@make -C $(LIBFT) -j
	@echo "$(_GREEN)[ LIBPRINTF DONE ]$(_END)"

$(NAME) : $(LIBFT)/$(LIBFTA) $(OBJ)
		@echo "\n"
		@echo "$(_RED)|_-_-_-_-_-_-_-_-_-_-_-_-|$(_END)"
		@echo "|    COMPILING FT-LS  |"
		@echo "$(_RED)|_-_-_-_-_-_-_-_-_-_-_-_-|$(_END)"
		@echo "\n"
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)/$(LIBFTA)
		@echo "$(_GREEN)[ FT-LS DONE ]$(_END)"

clean :
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ_PATH)
	@echo "$(_BLUE)======< CLEAN PROJECT & LIBPRINTF DONE >======$(_END)"
	@rm -f ./libprintf.a

fclean : clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)
	@echo "$(_BLUE)======< FCLEAN PROJECT & LIBPRINTF DONE >======$(_END)"

re : fclean all
