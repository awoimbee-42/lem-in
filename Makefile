# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 22:06:19 by marvin            #+#    #+#              #
#    Updated: 2019/04/09 19:20:05 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in

CFLAGS	=	-Wall -Wextra -g3 #-fsanitize=address #-Ofast -march=native -ftree-vectorize -fstrict-aliasing

SRC_NAME =	main.c					\
			\
			operators/t_str.c			\
			operators/t_map.c			\
			operators/t_graph.c			\
			operators/t_room.c			\
			operators/links.c			\
			\
			parser/get_input.c			\
			parser/utils.c				\
			parser/find_rooms.c			\
			parser/find_links.c			\
			parser/command_line.c		\
			\
			#pathfinding/find_paths.c

SRC_FOLDERS = parser pathfinding operators
################################################################################

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC = gcc
LDLIBS = -lft
LDFLAGS = -Llibft
CFLAGS += -I./ -I./libft -MMD

ifeq ($(OS),Linux)
		NUMPROC := $(shell grep -c ^processor /proc/cpuinfo)
else ifeq ($(OS),Darwin)
		NUMPROC := $(shell sysctl hw.ncpu | awk '{print $$2}')
endif

################################################################################

all :
	@make -j$(NUMPROC) $(NAME) --no-print-directory

libft/libft.a :
	@printf "$(YLW)Making libft...$(EOC)\n"
	@make -s -j$(NUMPROC) -C libft/

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

# Add rules written in .d files (by gcc -MMD)
# The '-' makes it doesn't care if the file exists or not
-include $(OBJ:.o=.d)

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
	make all
sfclean	:	objclean	outclean
sre		:	sfclean
	make all

.PHONY: all libclean objclean outclean clean fclean re sfclean sre

RED = \033[1;31m
GRN = \033[1;32m
YLW = \033[1;33m
INV = \033[7m
EOC = \033[0m
