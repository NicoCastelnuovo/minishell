/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/09 10:06:10 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "stdbool.h"
# include <signal.h>
# include <termcap.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "lexer.h"
# include "env.h"
# include "parser.h"
# include "executor.h"

typedef struct s_data
{
	t_env	*env;
	char	*input;
	t_list	*tokens;
	t_node	*tree;
	char	*err;
	int		e_code;
}	t_data;


// -------------------------------------------------------------------- SIGNALS
void	init_sig_handling(void);

// ------------------------------------------------------------------ EXPANSION
void	expansion(t_node *tree, t_env *env, int e_code);
char	*build_str(char *old_str, t_list *var_lst);
void	expand(char *s, t_env *env, int e_code);
void	del_to_expand(void *content);
void	print_expansion(t_list *var_lst);

// ---------------------------------------------------------------------- UTILS
void	free_data(t_data *data);

#endif
