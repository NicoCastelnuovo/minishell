/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/01 12:45:03 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"
# include "stdbool.h"
# include "lexer.h"
# include "env.h"
# include "parser.h"
# include "executor.h"
# include <signal.h>
# include <termcap.h>
# include <fcntl.h>

/*
	NOTE / TODO
	• SIGNALS
		- ctrl-D cause segfault
*/

typedef union i_need_all_of_those_possibility
{
	int		i;
	char	c;
	char	*s;
	long	l;
}	t_i_need;


void	tokenize_input(char *input, t_list **tkn_head);
char	*store_special_char_as_tkn(char *c, t_list **tkn_head);
char	*store_prev_chars_as_tkn(char *ref, int tkn_counter, t_list **tkn_head);
void	read_char(char cur_char, char **ref, int *tkn_ctr, t_list **tkn_head);
void	check_each_tkn_str(t_tkn_data *tkn_data);
void	detect_quote(t_tkn_data *tkn_data, char tkn_first_char, t_quote *position);
void	assign_type_to_tkn(t_list *tkns_head);
void	assign_quote_status_to_tkn(t_list *tkns_head);
void	merge_consecutive_less_or_greater_than(t_list *tkns_head);
void	delete_not_quoted_spaces(t_list **tkns_head);
void	merge_dollar_char_with_next_token(t_list *tkns_head);
void	merge_quoted_tokens(t_list *tkns_head);
void	free_token_data(void *content);
void	assign_following_space_status(t_list *tkns_head);
char	*join_two_strs(char **cur_str, char *next_str);
void	remove_next_node(t_list *cur_node);

// -------------------------------------------------------------------- SIGNALS
void	init_sig_handling(void);

// ------------------------------------------------------------------ EXPANSION
char	*build_str(char *old_str, t_list *var_lst);
char	*expansion(char *s, int exit_code, char **env);
void	del_var_lst_content(void *content);
void	print_var_lst(t_list *var_lst);

// void		update_env_var(char *name, char *value, char **env);
// t_var		*search_var(char *name, t_list *env);

#endif
