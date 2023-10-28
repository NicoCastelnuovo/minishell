/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/28 19:26:23 by fahmadia         ###   ########.fr       */
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

char	*store_special_char_as_tkn(char *c, t_list **tkn_head);
char	*store_prev_chars_as_tkn(char *ref, int tkn_counter, t_list **tkn_head);
void	read_char(char cur_char, char **ref, int *tkn_ctr, t_list **tkn_head);
void	check_each_tkn_str(t_token_data *tkn_data);
void	detect_quote(t_token_data *tkn_data, char tkn_first_char, t_quotation *position);
void	assign_type_to_tkn(t_list *tkns_head);
void	assign_quotation_to_tkn(t_list *tkns_head);
void	find_consecutive_less_or_greater_than(t_list *tkns_head);
void	free_tkn_str(void *content);
void	delete_spaces(t_list **tkns_head);
void	merge_dollar_char_with_next_token(t_list *tkns_head);
void	merge_quotations(t_list *tkns_head);
void	free_token_data(void *content);
void	free_tokens(t_list **token_head);

// ------------------------------------------------------------------ EXPANSION
char	*build_str(char *old_str, t_list *var_lst);
char	*expansion(char *s, int exit_code, char **env);
void	del_var_lst_content(void *content);
void	print_var_lst(t_list *var_lst);

// ------------------------------------------------------------------- BUILTINS
char	*get_wd(void);
int		cd(char *path, char **env);

// void		update_env_var(char *name, char *value, char **env);
// t_var		*search_var(char *name, t_list *env);

#endif
