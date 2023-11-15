# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 13:39:47 by fahmadia          #+#    #+#              #
#    Updated: 2023/11/15 15:01:55 by ncasteln         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GENERAL INSTRUCTIONS
#	Installing readline in Debian: apt-get install libreadline-dev
#	kill -9 $(jobs -ps) - kill all the suspended job, done with ctrl-Z

VPATH = ./src/ \
	./src/builtins \
	./src/env \
	./src/error \
	./src/executor \
	./src/expansion \
	./src/here_doc \
	./src/lexer \
	./src/parser \
	./src/print_utils \
	./src/signals \
	./src/utils \
	./test

BUILTINS = cd.c \
	print_env.c \
	echo.c \
	export.c \
	pwd.c \
	unset.c \
	exit.c

ERROR = error.c \

EXECUTOR = executor.c \
	parent.c \
	children.c \
	resolve_args.c \
	resolve_redir.c \
	run_builtin.c \

ENV = init_env.c \
	get_exported_var_n.c \
	create_var_content.c \
	del_var_content.c \
	get_env_custom.c \
	convert_to_dptr.c

EXPANSION = build_str.c \
	expansion.c

HERE_DOC = here_doc.c \

PARSER = check_for_syntax_err.c \
	build_syntax_tree.c \
	update_cmd_node.c \
	free_syntax_tree.c

PRINT_UTILS = print_syntax_tree.c \
	print_tokens.c \
	print_expansion.c \
	print_tree_construction.c

SIGNALS = sig_handler.c

UTILS = free_data.c \
	ft_strcmp.c \
	is_valid_for_history.c

LEXER = lexer.c \
	tokenize_input.c \
	del_tokens.c \
	store_tokens_in_nodes.c \
	read_each_char.c \
	check_each_token_string.c \
	handle_quotes.c \
	assign_quote_status_to_tokens.c \
	assign_type_to_tokens.c \
	merge_two_less_or_greater_than.c \
	delete_spaces.c \
	merge_dollar_char_with_next_token.c \
	merge_quoted_tokens.c \
	check_following_space.c \
	join_content_str_of_two_nodes.c \
	remove_a_token_node.c \

SRCS = minishell.c \
	$(BUILTINS) \
	$(ENV) \
	$(ERROR) \
	$(EXECUTOR) \
	$(EXPANSION) \
	$(HERE_DOC) \
	$(LEXER) \
	$(PARSER) \
	$(SYNTAX_TREE) \
	$(PRINT_UTILS) \
	$(SIGNALS) \
	$(UTILS)

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
