# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 13:39:47 by fahmadia          #+#    #+#              #
#    Updated: 2023/10/27 16:38:49 by fahmadia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GENERAL INSTRUCTIONS
# Installing readline in Debian: apt-get install libreadline-dev

VPATH = ./src/lexer\
	./src/helpers/linked_lists\
	./src/memory_management

SRCS = main.c\
	free_tokens.c\
	store_tokens_in_nodes.c\
	read_each_char.c\
	check_each_token_string.c\
	handle_quotes.c\
	assign_position_and_type_to_tokens.c\
	merge_two_less_or_greater_than.c\
	delete_spaces.c\

OBJS_PATH = ./objs
OBJS = $(patsubst %.c, $(OBJS_PATH)/%.o, $(SRCS))

CC = cc
CFLAGS = -c -g -Wall -Wextra #-Werror
NAME = minishell
MYLIB_PATH = ./mylib
MYLIB = $(MYLIB_PATH)/libmylib.a
INCLUDE = -I./include -I./mylib/libft -I./mylib/ft_printf -I./mylib/get_next_line

COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_END = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(MYLIB) Makefile
	@$(CC) $(OBJS) -L$(MYLIB_PATH) -lmylib -lreadline -o $(NAME)
	@echo "$(COLOR_GREEN)minishell is created.$(COLOR_END)"

$(OBJS_PATH)/%.o: %.c
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

$(MYLIB):
	@cd $(MYLIB_PATH) && make

clean:
	@rm -f $(OBJS)
	@cd ./$(MYLIB_PATH) && make clean
	@echo "$(COLOR_YELLOW)minishell object files are deleted.$(COLOR_END)"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJS_PATH)
	@cd ./$(MYLIB_PATH) && make fclean
	@echo "$(COLOR_YELLOW)minishell object files and minishell executable file are deleted.$(COLOR_END)"

re: fclean all

.PHONY: all clean fclean re
