# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 22:06:19 by marvin            #+#    #+#              #
#    Updated: 2019/03/14 17:42:58 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in

CC = gcc

CFLAGS	=	-Wall -Wextra -g3 #-Ofast -march=native -ftree-vectorize -fstrict-aliasing

SRC_NAME =	main.c							

SRC_FOLDERS = parser
################################################################################

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LDLIBS = -lft

LDFLAGS = -Llibft 

CFLAGS += -I./ -I./libft

################################################################################

all : $(NAME)

libft/libft.a :
	@printf "$(YLW)Making libft...$(EOC)\n"
	@make -s -j -C libft/

$(NAME) : libft/libft.a $(OBJ) lem_in.h
	@printf "$(GRN)Linking $(NAME)...$(EOC)\n"
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_PATH) :
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@mkdir -p $(addprefix $(OBJ_PATH)/,$(SRC_FOLDERS)) 2> /dev/null
	@printf "$(GRN)Building with \"$(CFLAGS)\":$(EOC)\n"

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c | $(OBJ_PATH)
	@printf "\t$(CC) (...) $@\n"
	@$(CC) $(CFLAGS) -o $@ -c $<

libclean :
	@printf "$(YLW)Cleaning libft...$(EOC)\n"
	@make -s fclean -C libft

objclean :
	@rm -rf $(OBJ_PATH)
	@printf "$(RED)$(OBJ_PATH) removed$(EOC)\n"

outclean :
	@rm -f $(NAME)
	@printf "$(RED)$(NAME) removed$(EOC)\n"

clean	:	libclean	objclean
fclean	:	clean		outclean
re		:	fclean
	make -sj all
sfclean	:	objclean	outclean
sre		:	sfclean
	make -sj $(NAME)

.PHONY: all libclean objclean outclean clean fclean re sfclean sre

RED = \033[1;31m
GRN = \033[1;32m
YLW = \033[1;33m
INV = \033[7m
EOC = \033[0m
