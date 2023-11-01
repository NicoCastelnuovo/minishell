# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 13:39:47 by fahmadia          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/10/28 11:12:50 by ncasteln         ###   ########.fr        #
=======
#    Updated: 2023/10/30 15:08:16 by fahmadia         ###   ########.fr        #
>>>>>>> a76193577c0ac34361ef1ab1f4f8e330e5b0ff55
#                                                                              #
# **************************************************************************** #

# GENERAL INSTRUCTIONS
# Installing readline in Debian: apt-get install libreadline-dev

VPATH = ./src/ \
	./src/lexer\
	./src/helpers/linked_lists\
	./src/memory_management\
	./test\
	./src/builtins \
	./src/env_dlst \
	./src/signals

SRCS = main.c\
	tokenize_input.c\
	free.c\
	store_tokens_in_nodes.c\
	read_each_char.c\
	check_each_token_string.c\
	handle_quotes.c\
	assign_quote_status_to_tokens.c\
	assign_type_to_tokens.c\
	merge_two_less_or_greater_than.c\
	delete_spaces.c\
	merge_dollar_char_with_next_token.c\
	merge_quoted_tokens.c\
	check_following_space.c\
	join_content_str_of_two_nodes.c\
	remove_a_token_node.c\
	minishell.c \
	env.c \
	env_dlst_append.c \
	env_dlst_clear.c \
	env_dlst_delnode.c \
	env_dlst_new.c \
	env_dlst_update.c \
	sig_handler.c

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
	@$(CC) $(OBJS) -L$(MYLIB_PATH) -lmylib -lreadline -ltermcap -o $(NAME)
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
