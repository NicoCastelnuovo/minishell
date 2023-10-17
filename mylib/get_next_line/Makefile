# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 15:31:49 by fahmadia          #+#    #+#              #
#    Updated: 2023/10/11 10:43:17 by fahmadia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = get_next_line_utils.c\
	get_next_line.c\

BONUS = get_next_line_bonus.c\
	get_next_line_utils_bonus.c\
	
CC = cc

CFLAGS = -c -g -Wall -Wextra -Werror

NAME = getnextline.a

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

COLOR_GREEN = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_END = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_FLAG) Makefile
	@ar rcs $(NAME) $(OBJS)
	@echo "$(COLOR_GREEN)get_next_line.a is created without bonus object files.$(COLOR_END)"

%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@echo "$(COLOR_YELLOW)get_next_line object files are deleted.$(COLOR_END)"

fclean: clean
	@rm -f $(OBJS_FLAG)
	@rm -f $(BONUS_PATH)/bonus_flag
	@rm -f $(NAME) 
	@echo "$(COLOR_YELLOW)get_next_line object files and get_next_line.a are deleted.$(COLOR_END)"
re: fclean $(NAME)

bonus: $(OBJS) $(BONUS_OBJS)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(COLOR_GREEN)get_next_line.a is created with bonus object files.$(COLOR_END)"

.PHONY: all clean fclean re bonus
