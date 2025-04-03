# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 19:22:50 by gangel-a          #+#    #+#              #
#    Updated: 2025/03/17 19:22:50 by gangel-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
NAME = philosophers

# COMPILATION AND FLAGS
CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra -Iinclude -lpthread -fsanitize=thread -g

# PATHS
SRC_DIR = src/
OBJ_DIR = obj/

# MANDATORY FILES AND OBJECTS
SRC = $(wildcard $(SRC_DIR)*.c)
OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRC:%.c=%.o)))

# ------------------------------ Colors ------------------------------

BLUE		=	\033[0;34m
BLUE_BOLD	=	\033[1;34m
GREEN_BOLD	=	\033[1;92m
YELLOW_BOLD	=	\033[1;93m
YELLOW		=	\033[0;33m
RED			=	\033[0;91m
MAGENTA 	=	\033[1;35m
MAGENTA_BOLD = \033[1;35m
CYAN		=	\033[0;96m
CYAN_BOLD	=	\033[1;36m
RESET		=	\033[0m

# ------------------------------ Rules ------------------------------

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@printf "$(BLUE)$@: $(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(GREEN_BOLD)Object compiled.$(RESET)\n"

$(NAME): $(OBJ)
	@printf "$(GREEN_BOLD) => 100%%$(RESET)\n"
	@printf "$(MAGENTA_BOLD)[philosophers]:\t$(RESET)"
	$(CC) $(CFLAGS) $(OBJ) $(LIB_PATHS) -o $@
	@printf "$(GREEN_BOLD) => Success!$(RESET)\n"

norm:
	@echo "\n$(YELLOW_BOLD)======= MANDATORY =======$(RESET)"
	@norminette src | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/Error/\x1b[1;31m&\x1b[0m/g'
	@echo "\n$(MAGENTA_BOLD)======= INCLUDES =======$(RESET)"
	@norminette include | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/Error/\x1b[1;31m&\x1b[0m/g'

leak: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./$(NAME) <args>

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(MAGENTA_BOLD)[philosophers]:\tobject files$(RESET)$(GREEN_BOLD)  => Cleaned!$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(MAGENTA_BOLD)[philosophers]:\texec. files$(RESET)$(GREEN_BOLD)  => Cleaned!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re leak norm
