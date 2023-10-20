/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/20 16:03:23 by ncasteln         ###   ########.fr       */
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
# include "typedef.h"

t_token	*create_node(void *content, int type);
t_token	*add_node_to_linked_list(t_token *head, void *content, int type);

// ------------------------------------------------------------------ EXPANSION
char	*build_str(char *old_str, t_list *var_lst);
char	*expansion(char *s, int exit_code, char **env);
void	del_var_lst(void *content);
void	print_var_lst(t_list *var_lst);

// -------------------------------------------------------------------- BULTINS
int			echo(char *s);
const char	*get_wd(char *opt);
int			cd(char *path, char **env);
char		*get_env_var(char *name, char **env);
char		**copy_env(char **envp);
void		print_env(char **env);

// ---------------------------------------------------------------------- UTILS

#endif
