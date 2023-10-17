# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 15:20:22 by fahmadia          #+#    #+#              #
#    Updated: 2023/10/11 09:15:28 by fahmadia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmylib.a
COPY_DEST = ./
OBJS = ./*.o

LIBFT_LIB = ./libft/libft.a
LIBFT = ./libft

LIBFTPRINTF_LIB = ./ft_printf/libftprintf.a
LIBFTPRINTF = ./ft_printf

GETNEXTLINE_LIB = ./get_next_line/getnextline.a
GETNEXTLINE = ./get_next_line

COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_END = \033[0m

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(LIBFTPRINTF_LIB) $(GETNEXTLINE_LIB) 
	@make extract
# @make clean
	
extract:
	@cp $(LIBFT_LIB) $(COPY_DEST)
	@cp $(LIBFTPRINTF_LIB) $(COPY_DEST)
	@cp $(GETNEXTLINE_LIB) $(COPY_DEST)
	@ar x ./libft.a
	@ar x ./libftprintf.a
	@ar x ./getnextline.a
	@ar rcs $(NAME) $(OBJS)
	@rm -f $(OBJS) "__.SYMDEF SORTED" ./libft.a ./libftprintf.a ./getnextline.a
	@rm -f "__.SYMDEF SORTED" ./libft.a ./libftprintf.a ./getnextline.a
	@echo "$(COLOR_GREEN)libft.a, ft_printf.a, and get_next_line.a are merged and libmylib.a is created.$(COLOR_END)"

$(LIBFT_LIB): 
	@make bonus -C $(LIBFT)

$(LIBFTPRINTF_LIB):
	@make -C $(LIBFTPRINTF)

$(GETNEXTLINE_LIB):
	@make -C $(GETNEXTLINE)

clean: 
	@rm -f $(OBJS)
	@cd $(LIBFT) && make clean
	@cd $(LIBFTPRINTF) && make clean
	@cd $(GETNEXTLINE) && make clean

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make fclean -C $(LIBFTPRINTF)
	@make fclean -C $(GETNEXTLINE)

re: 
	@make fclean
	@make $(NAME)

.PHONY: all clean fclean re
