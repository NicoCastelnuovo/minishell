/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/23 14:39:20 by ncasteln         ###   ########.fr       */
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
void	del_var_lst_content(void *content);
void	print_var_lst(t_list *var_lst);

// -------------------------------------------------------------------- BULTINS
int			echo(char *s);
const char	*get_wd(char *opt);
int			cd(char *path, char **env);
void		export(char *new_var);

// ------------------------------------------------------------------------ ENV
t_dlist		*init_env(char **env);
void		print_env(t_dlist *env);
t_var		*search_var(char *name, t_list *env);			// replicates getenv() function
void		update_env_var(char *name, char *value, char **env);
void		unset_env_var(char *name, t_dlist **env);

// ---------------------------------------------------------------------- UTILS
t_dlist		*dlst_new(void *content);
t_dlist		*dlst_last(t_dlist *lst);
void		dlst_append(t_dlist **lst, t_dlist *new);
void		dlist_delnode(t_dlist **node, void (*del)(void *));

#endif
