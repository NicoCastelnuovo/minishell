/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/14 17:07:37 by ncasteln         ###   ########.fr       */
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
# include <termcap.h> // ???
# include <termios.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "lexer.h"
# include "env.h"
# include "parser.h"

typedef struct s_data
{
	t_list	*env;
	char	*input;
	t_list	*tokens;
	t_node	*tree;
	char	*err;
	int		e_code;
	int		n_ps;
	int		*pid;
}	t_data;

/*
	Custom error values are in the range between 106 (max errno value) and
	126 (min reserved exit code), excluded.
*/
enum e_custom_errors
{
	CE_INVARG = 107,
	CE_CMDNOTFOUND = 127
};

// -------------------------------------------------------------------- SIGNALS
void	init_sig_handling(void);

// ------------------------------------------------------------------ EXPANSION
void	expansion(t_node *tree, t_list *env, int e_code);
char	*build_str(char *old_str, t_list *var_lst);
char	*expand(char *s, t_list *env, int e_code);
void	del_to_expand(void *content);
void	print_expansion(t_list *var_lst);

// ------------------------------------------------------------------- HERE_DOC
void	here_doc(t_node *tree, t_data *data);

// ------------------------------------------------------------------- EXECUTOR
int		executor(t_data *data);
int		parent(t_data *data);
void	first_child(t_cmd *cmd, char **env, int *fd_pipe);
void	mid_child(t_cmd *cmd, char **env, int *fd_pipe, int *prev_pipe);
void	last_child(t_cmd *cmd, char **env, int *fd_pipe, int *prev_pipe);
void	resolve_args(char **cmd_name, char **env);
int		resolve_redir(t_cmd *cmd);

// ------------------------------------------------------------------- BUILTINS
void	print_env(t_list *env);
void	cd(t_data *data);
void	pwd(void);
void	exit_custom(t_data *data);
void	unset(t_data *data);
void	get_exported(t_list *env);
void	export(t_data *data);
void	echo(t_data *data);

// ---------------------------------------------------------------------- UTILS
void	error(char *msg, int n);
int		ft_strcmp(const char *s1, const char *s2);
void	free_data(t_data *data);
int		get_substr_len(char *s, char c);
int		is_valid_for_history(t_data *data);
int		is_empty_input(char *s);

#endif
