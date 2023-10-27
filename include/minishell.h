/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/27 10:06:26 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"
# include "typedef.h"
# include "stdbool.h"

char	*store_special_char_as_tkn(char *c, t_list **tkn_head);
char	*store_prev_chars_as_tkn(char *ref, int tkn_counter, t_list **tkn_head);
void	read_char(char cur_char, char **ref, int *tkn_ctr, t_list **tkn_head);
void	check_each_tkn_str(t_token_data *tkn_data);
void	detect_quote(char tkn_first_char, t_quotation *position);
void	assign_type_to_tkn(t_list *tkns_head);
void	assign_quotation_to_tkn(t_list *tkns_head);
int		lexer(void);

void			free_tokens(t_list **token_head);

#endif
