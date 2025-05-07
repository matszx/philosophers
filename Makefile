# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 12:32:24 by mcygan            #+#    #+#              #
#    Updated: 2025/05/07 14:12:52 by mcygan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	philo
CC 				=	gcc
CFLAGS 			=	-Wall -Wextra -Werror -pthread -O3 #-fsanitize=thread	

SRC_FILES 		=	main.c \
					routine.c \
					monitor.c \
					utils.c

SRC_DIR			=	src/
SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR			=	obj/
OBJ				=	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# ---------------------------------------------------------------------------- #

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
					@$(CC) $(CFLAGS) -c $< -o $@

all				:	$(OBJ_DIR) $(NAME)

$(OBJ_DIR)		:
					@mkdir -p $(OBJ_DIR)

$(NAME)			:	$(OBJ)
					# compiling $(NAME)
					@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
					# ready

clean			:
					# cleaning up
					@rm -rf $(OBJ_DIR)

fclean			:	clean
					@rm -f $(NAME)
					# $(NAME) deleted			

re				:	fclean all

.PHONY			:	all clean flcean re
